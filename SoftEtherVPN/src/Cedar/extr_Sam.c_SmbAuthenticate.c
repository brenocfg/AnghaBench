#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  requiremember ;
typedef  int /*<<< orphan*/  ntlm_timeout ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  answer ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  Buf; } ;
typedef  scalar_t__ PID ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 unsigned int B64_Encode (char*,char*,int) ; 
 int /*<<< orphan*/  CloseChildProcess (scalar_t__,int*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* CopyBinToStr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 unsigned int Decode64 (char*,char*) ; 
 int /*<<< orphan*/  EnSafeStr (char*,char) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 scalar_t__ OpenChildProcess (char*,char**,int*) ; 
 TYPE_1__* StrToBin (char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 int base64_enc_len (unsigned int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

bool SmbAuthenticate(char* name, char* password, char* domainname, char* groupname, UINT timeout, UCHAR* challenge8, UCHAR* MsChapV2_ClientResponse, UCHAR* nt_pw_hash_hash)
{
	bool  auth = false;
	int   fds[2];
	FILE* out, *in;
	PID   pid;
	char  buffer[255];
	char  ntlm_timeout[32];
	char* proc_parameter[6];
	
	if (name == NULL || password == NULL || domainname == NULL || groupname == NULL)
	{
		Debug("Sam.c - SmbAuthenticate - wrong password parameter\n");
		return false;
	}

	if (password[0] == '\0' && (challenge8 == NULL || MsChapV2_ClientResponse == NULL || nt_pw_hash_hash == NULL))
	{
		Debug("Sam.c - SmbAuthenticate - wrong MsCHAPv2 parameter\n");
		return false;
	}

	Zero(buffer, sizeof(buffer));

	// Truncate string if unsafe char
	EnSafeStr(domainname, '\0');

	if (strlen(domainname) > 255)
	{
		// there is no domainname longer then 255 chars!
		// http://tools.ietf.org/html/rfc1035 section 2.3.4
		domainname[255] = '\0';
	}
	
	// set timeout to 15 minutes even if timeout is disabled, to prevent ntlm_auth from hung up
	if (timeout <= 0 || timeout > 900)
	{
		timeout = 999;
	}
	
	snprintf(ntlm_timeout, sizeof(ntlm_timeout), "%is", timeout);
	Debug("Sam.c - timeout for ntlm_auth %s\n", ntlm_timeout);

	proc_parameter[0] = "timeout";
	proc_parameter[1] = ntlm_timeout;
	proc_parameter[2] = "ntlm_auth";
	proc_parameter[3] = "--helper-protocol=ntlm-server-1";
	proc_parameter[4] = 0;

	if (strlen(groupname) > 1)
	{
		// DNS Name 255 chars + OU names are limited to 64 characters +  cmdline 32 + 1
		char  requiremember[352];

		// Truncate string if unsafe char
		EnSafeStr(groupname, '\0');

		snprintf(requiremember, sizeof(requiremember), "--require-membership-of=%s\\%s", domainname, groupname);
		
		proc_parameter[4] = requiremember;
		proc_parameter[5] = 0;
	}

	pid = OpenChildProcess("timeout", proc_parameter, fds);

	if (pid < 0)
	{
		Debug("Sam.c - SmbCheckLogon - error fork child process (ntlm_auth)\n");
		return false;
	}

	out = fdopen(fds[1], "w");
	if (out == 0)
	{
		CloseChildProcess(pid, fds);

		Debug("Sam.c - cant open out pipe (ntlm_auth)\n");
		return false;
	}

	in = fdopen(fds[0], "r");
	if (in == 0)
	{
		fclose(out);
		CloseChildProcess(pid, fds);

		Debug("Sam.c - cant open in pipe (ntlm_auth)\n");
		return false;
	}

	if (base64_enc_len((unsigned int)strlen(name)) < sizeof(buffer)-1 &&
		base64_enc_len((unsigned int)strlen(password)) < sizeof(buffer)-1 &&
		base64_enc_len((unsigned int)strlen(domainname)) < sizeof(buffer)-1)
	{
		char  answer[300];

		unsigned int end = B64_Encode(buffer, name, (int)strlen(name));
		buffer[end] = '\0';
		fputs("Username:: ", out);
		fputs(buffer, out);
		fputs("\n", out);
		Debug("Username: %s\n", buffer);
		buffer[0] = 0;

		end = B64_Encode(buffer, domainname, (int)strlen(domainname));
		buffer[end] = '\0';
		fputs("NT-Domain:: ", out);
		fputs(buffer, out);
		fputs("\n", out);
		Debug("NT-Domain: %s\n", buffer);
		buffer[0] = 0;

		if (password[0] != '\0')
		{
			Debug("Password authentication\n");
			end = B64_Encode(buffer, password, (int)strlen(password));
			buffer[end] = '\0';
			fputs("Password:: ", out);
			fputs(buffer, out);
			fputs("\n", out);
			Debug("Password: %s\n", buffer);
			buffer[0] = 0;
		}
		else
		{
			char* mschapv2_client_response;
			char* base64_challenge8;

			Debug("MsChapV2 authentication\n");
			mschapv2_client_response = CopyBinToStr(MsChapV2_ClientResponse, 24);
			end = B64_Encode(buffer, mschapv2_client_response, 48);
			buffer[end] = '\0';
			fputs("NT-Response:: ", out);
			fputs(buffer, out);
			fputs("\n", out);
			Debug("NT-Response:: %s\n", buffer);
			buffer[0] = 0;
			Free(mschapv2_client_response);

			base64_challenge8 = CopyBinToStr(challenge8, 8);
			end = B64_Encode(buffer, base64_challenge8 , 16);
			buffer[end] = '\0';
			fputs("LANMAN-Challenge:: ", out);
			fputs(buffer, out);
			fputs("\n", out);
			Debug("LANMAN-Challenge:: %s\n", buffer);
			buffer[0] = 0;
			Free(base64_challenge8);

			fputs("Request-User-Session-Key: Yes\n", out);
 		}

		// Start authentication
		fputs( ".\n", out );
		fflush (out);
		// Request send!

		Zero(answer, sizeof(answer));

		while (fgets(answer, sizeof(answer)-1, in))
		{
			char* response_parameter;

			if (strncmp(answer, ".\n", sizeof(answer)-1 ) == 0)
			{
				break;
			}

			/* Indicates a base64 encoded structure */
			response_parameter = strstr(answer, ":: ");
			if (!response_parameter) {
				char* newline;

				response_parameter = strstr(answer, ": ");

				if (!response_parameter) {
					continue;
				}

				response_parameter[0] ='\0';
				response_parameter++;
				response_parameter[0] ='\0';
				response_parameter++;

				newline  = strstr(response_parameter, "\n");
				if( newline )
					newline[0] = '\0';
			} else {
				response_parameter[0] ='\0';
				response_parameter++;
				response_parameter[0] ='\0';
				response_parameter++;
				response_parameter[0] ='\0';
				response_parameter++;

				end = Decode64(response_parameter, response_parameter);
				response_parameter[end] = '\0';
			}

			if (strncmp(answer, "Authenticated", sizeof(answer)-1 ) == 0)
			{
				if (strcmp(response_parameter, "Yes") == 0)
				{
					Debug("Authenticated!\n");
					auth = true;
				}
				else if (strcmp(response_parameter, "No") == 0)
				{
					Debug("Authentication failed!\n");
					auth = false;
				}
			}
			else if (strncmp(answer, "User-Session-Key", sizeof(answer)-1 ) == 0)
			{
				if (nt_pw_hash_hash != NULL)
				{
					BUF* Buf = StrToBin(response_parameter);
					Copy(nt_pw_hash_hash, Buf->Buf, 16);
					FreeBuf(Buf);
				}
			}
		}
	}

	fclose(in);
	fclose(out);

	CloseChildProcess(pid, fds);

	return auth;
}