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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int size; char* data; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ WU_WEBPAGE ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CalcUniToUtf8 (int /*<<< orphan*/ *) ; 
 char* HTTP_CONTENT_TYPE4 ; 
 char* HTTP_KEEP_ALIVE ; 
 scalar_t__ Malloc (int) ; 
 int /*<<< orphan*/  NewHttpHeader (char*,char*,char*) ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 
 int /*<<< orphan*/  UniToUtf8 (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static WU_WEBPAGE *WuNewUniWebPage(wchar_t *content)
{
	WU_WEBPAGE *ret;

	if(content == NULL)
	{
		return NULL;
	}

	ret = (WU_WEBPAGE*)Malloc(sizeof(WU_WEBPAGE));
	ret->size = CalcUniToUtf8(content);
	ret->data = (char*)Malloc(ret->size);
	UniToUtf8(ret->data, ret->size, content);

	ret->header = NewHttpHeader("HTTP/1.1", "202", "OK");
	AddHttpValue(ret->header, NewHttpValue("Content-Type", HTTP_CONTENT_TYPE4));
	AddHttpValue(ret->header, NewHttpValue("Connection", "Keep-Alive"));
	AddHttpValue(ret->header, NewHttpValue("Keep-Alive", HTTP_KEEP_ALIVE));

	return ret;
}