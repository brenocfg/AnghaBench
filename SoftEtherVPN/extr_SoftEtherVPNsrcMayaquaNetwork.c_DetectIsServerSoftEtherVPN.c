#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  ip_str ;
typedef  int UINT ;
struct TYPE_12__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_11__ {int /*<<< orphan*/  RemoteIP; } ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (char*,int /*<<< orphan*/ ,int) ; 
 char* DEFAULT_USER_AGENT ; 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeHttpHeader (int /*<<< orphan*/ *) ; 
 int GetContentLength (int /*<<< orphan*/ *) ; 
 char* HTTP_KEEP_ALIVE ; 
 char* HttpHeaderToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ InStr (char*,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int MIN (int,int) ; 
 void* Malloc (int) ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/ * NewHttpHeaderEx (char*,char*,char*,int) ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 
 int Recv (TYPE_1__*,void*,int,int) ; 
 int /*<<< orphan*/ * RecvHttpHeader (TYPE_1__*) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SendAll (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ StartWith (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,void*,int) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 int /*<<< orphan*/  http_detect_server_startwith ; 
 int /*<<< orphan*/  http_detect_server_tag_future ; 

bool DetectIsServerSoftEtherVPN(SOCK *s)
{
	HTTP_HEADER *h;
	char ip_str[MAX_SIZE];
	char *send_str;
	UINT content_len;
	BUF *recv_buf;
	void *socket_buffer;
	UINT socket_buffer_size = 32768;
	bool ok = false;
	// Validate arguments
	if (s == NULL)
	{
		return false;
	}

	IPToStr(ip_str, sizeof(ip_str), &s->RemoteIP);

	// Request generation
	h = NewHttpHeaderEx("GET", "/", "HTTP/1.1", true);
	AddHttpValue(h, NewHttpValue("X-VPN", "1"));
	AddHttpValue(h, NewHttpValue("Host", ip_str));
	AddHttpValue(h, NewHttpValue("Keep-Alive", HTTP_KEEP_ALIVE));
	AddHttpValue(h, NewHttpValue("Connection", "Keep-Alive"));
	AddHttpValue(h, NewHttpValue("Accept-Language", "ja"));
	AddHttpValue(h, NewHttpValue("User-Agent", DEFAULT_USER_AGENT));
	AddHttpValue(h, NewHttpValue("Pragma", "no-cache"));
	AddHttpValue(h, NewHttpValue("Cache-Control", "no-cache"));



	send_str = HttpHeaderToStr(h);
	FreeHttpHeader(h);

	// Transmission
	if (SendAll(s, send_str, StrLen(send_str), true) == false)
	{
		Free(send_str);
		return false;
	}

	Free(send_str);

	// Receive
	h = RecvHttpHeader(s);
	if (h == NULL)
	{
		return false;
	}

	// Get the length of the content
	content_len = GetContentLength(h);
	FreeHttpHeader(h);

	if (content_len == 0 || content_len >= (1024 * 1024))
	{
		return false;
	}

	// Receive contents
	recv_buf = NewBuf();
	socket_buffer = Malloc(socket_buffer_size);

	while (true)
	{
		UINT recvsize = MIN(socket_buffer_size, content_len - recv_buf->Size);
		UINT size;

		if (recvsize == 0)
		{
			ok = true;
			break;
		}

		size = Recv(s, socket_buffer, recvsize, true);
		if (size == 0)
		{
			// Disconnected
			break;
		}

		WriteBuf(recv_buf, socket_buffer, size);
	}

	SeekBuf(recv_buf, 0, 0);
	Free(socket_buffer);

	if (ok)
	{
		// Examine to confirm whether the incoming data is a SoftEther VPN protocol
		char tmp[1024];

		Zero(tmp, sizeof(tmp));

		Copy(tmp, recv_buf->Buf, MIN(recv_buf->Size, (sizeof(tmp) - 1)));

		ok = false;

		if (StartWith(tmp, http_detect_server_startwith))
		{
			ok = true;
		}
		else if (InStr(tmp, http_detect_server_tag_future))
		{
			ok = true;
		}
	}

	FreeBuf(recv_buf);

	return ok;
}