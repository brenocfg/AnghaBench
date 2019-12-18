#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  url2 ;
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  filename ;
typedef  size_t UINT ;
struct TYPE_6__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  int /*<<< orphan*/  CONNECTION ;
typedef  TYPE_1__ BUF ;
typedef  int /*<<< orphan*/  ADMIN ;

/* Variables and functions */
 TYPE_1__* AdminWebProcessServerSideInclude (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int AdminWebSend302Redirect (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int AdminWebSend404Error (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int AdminWebSendBody (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* AdminWebTryFindAndReadFile (char*,char*,char*,char*,int,int*) ; 
 int EndWith (char*,char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 char* GetMimeTypeFromFileName (char*) ; 
 scalar_t__ InStr (char*,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 size_t StrLen (char*) ; 
 int /*<<< orphan*/  TrimEndWith (char*,int,char*,char*) ; 

bool AdminWebHandleFileRequest(ADMIN *a, CONNECTION *c, SOCK *s, HTTP_HEADER *h, char *url_src, char *query_string, char *virtual_root_dir, char *physical_root_dir)
{
	bool ret = false;
	char url[MAX_PATH];
	UINT i, len;
	if (a == NULL || c == NULL || s == NULL || h == NULL || query_string == NULL ||
		virtual_root_dir == NULL || physical_root_dir == NULL)
	{
		return false;
	}

	StrCpy(url, sizeof(url), url_src);

	len = StrLen(url);
	for (i = 0;i < len;i++)
	{
		if (url[i] == '\\')
		{
			url[i] = '/';
		}
	}

	// Is dangerous URL?
	if (InStr(url, "..") || InStr(url, "//") || InStr(url, "\\\\") || InStr(url, "/\\") || InStr(url, "\\/"))
	{
		ret = AdminWebSend404Error(s, h);
	}
	else
	{
		char filename[MAX_PATH];
		bool is_index_file = false;

		BUF *b = AdminWebTryFindAndReadFile(virtual_root_dir, physical_root_dir, url,
			filename, sizeof(filename), &is_index_file);

		if (b == NULL)
		{
			ret = AdminWebSend404Error(s, h);
		}
		else
		{
			if (is_index_file && EndWith(url, "/") == false)
			{
				char url2[MAX_PATH];
				StrCpy(url2, sizeof(url2), url);
				StrCat(url2, sizeof(url2), "/");
				ret = AdminWebSend302Redirect(s, url2, query_string, h);
			}
			else if (is_index_file == false && EndWith(url, "/"))
			{
				char url2[MAX_PATH];
				TrimEndWith(url2, sizeof(url2), url, "/");
				ret = AdminWebSend302Redirect(s, url2, query_string, h);
			}
			else
			{
				BUF *b2 = AdminWebProcessServerSideInclude(b, filename, 0);
				char *mime = GetMimeTypeFromFileName(filename);

				if (mime == NULL)
				{
					mime = "application/octet-stream";
				}

				ret = AdminWebSendBody(s, 200, "OK", b2->Buf, b2->Size, mime, NULL, NULL, h);

				FreeBuf(b2);
			}
			FreeBuf(b);
		}
	}

	return ret;
}