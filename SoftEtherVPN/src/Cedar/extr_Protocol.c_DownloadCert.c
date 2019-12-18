#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  URL_DATA ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BufToX (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CERT_HTTP_DOWNLOAD_MAXSIZE ; 
 int /*<<< orphan*/  CERT_HTTP_DOWNLOAD_TIMEOUT ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HttpRequestEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsBase64 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int ParseUrl (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

X *DownloadCert(char *url)
{
	BUF *b;
	URL_DATA url_data;
	X *ret = NULL;
	// Validate arguments
	if (IsEmptyStr(url))
	{
		return NULL;
	}

	Debug("Trying to download a cert from %s ...\n", url);

	if (ParseUrl(&url_data, url, false, NULL) == false)
	{
		Debug("Download failed.\n");
		return NULL;
	}

	b = HttpRequestEx(&url_data, NULL, CERT_HTTP_DOWNLOAD_TIMEOUT, CERT_HTTP_DOWNLOAD_TIMEOUT,
		NULL, false, NULL, NULL, NULL, NULL, NULL, CERT_HTTP_DOWNLOAD_MAXSIZE);

	if (b == NULL)
	{
		Debug("Download failed.\n");
		return NULL;
	}

	ret = BufToX(b, IsBase64(b));

	FreeBuf(b);

	Debug("Download ok.\n");
	return ret;
}