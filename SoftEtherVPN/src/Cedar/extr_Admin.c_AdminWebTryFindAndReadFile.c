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
typedef  int /*<<< orphan*/  tmp3 ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  relative_path ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * AdminWebTryOneFile (char*,char*,int) ; 
 int /*<<< orphan*/  CombinePath (char*,int,char*,char*) ; 
 int MAX_PATH ; 
 int StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 

BUF *AdminWebTryFindAndReadFile(char *vroot, char *proot, char *url, char *ret_filename, UINT ret_filename_size, bool *is_index_html)
{
	char tmp[MAX_PATH];
	char tmp2[MAX_PATH];
	UINT vroot_len;
	UINT url_len;
	char relative_path[MAX_PATH];
	BUF *b;
	if (vroot == NULL || proot == NULL || url == NULL || ret_filename == NULL || is_index_html == NULL)
	{
		return NULL;
	}

	*is_index_html = false;

	if (StartWith(url, vroot) == false)
	{
		return NULL;
	}

	vroot_len = StrLen(vroot);
	url_len = StrLen(url);

	StrCpy(relative_path, sizeof(relative_path), url + vroot_len);

	if (StartWith(relative_path, "/"))
	{
		char tmp3[MAX_PATH];

		StrCpy(tmp3, sizeof(tmp3), relative_path + 1);
		StrCpy(relative_path, sizeof(relative_path), tmp3);
	}

	CombinePath(tmp, sizeof(tmp), proot, relative_path);

	// index.html
	CombinePath(tmp2, sizeof(tmp2), tmp, "index.html");
	b = AdminWebTryOneFile(tmp2, ret_filename, ret_filename_size);
	if (b != NULL)
	{
		*is_index_html = true;
		return b;
	}

	// dirname/filename
	StrCpy(tmp2, sizeof(tmp2), tmp);
	b = AdminWebTryOneFile(tmp2, ret_filename, ret_filename_size);
	if (b != NULL)
	{
		return b;
	}

	return NULL;
}