#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; char* data; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ WU_WEBPAGE ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (char*,char*,int) ; 
 scalar_t__ EndWith (char*,char*) ; 
 char* HTTP_CONTENT_TYPE3 ; 
 char* HTTP_CONTENT_TYPE4 ; 
 char* HTTP_KEEP_ALIVE ; 
 scalar_t__ Malloc (int) ; 
 int /*<<< orphan*/  NewHttpHeader (char*,char*,char*) ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 

__attribute__((used)) static WU_WEBPAGE *WuNewWebPage(char *content, UINT size, char *filename)
{
	WU_WEBPAGE *ret;

	if(content == NULL)
	{
		return NULL;
	}

	ret = (WU_WEBPAGE*)Malloc(sizeof(WU_WEBPAGE));
	ret->size = size;
	ret->data = (char*)Malloc(size);
	Copy(ret->data, content, size);

	ret->header = NewHttpHeader("HTTP/1.1", "202", "OK");
	AddHttpValue(ret->header, NewHttpValue("Connection", "Keep-Alive"));
	AddHttpValue(ret->header, NewHttpValue("Keep-Alive", HTTP_KEEP_ALIVE));

	if(EndWith(filename, "jpg"))
	{
		AddHttpValue(ret->header, NewHttpValue("Content-Type", HTTP_CONTENT_TYPE3));
	}
	AddHttpValue(ret->header, NewHttpValue("Content-Type", HTTP_CONTENT_TYPE4));

	return ret;
}