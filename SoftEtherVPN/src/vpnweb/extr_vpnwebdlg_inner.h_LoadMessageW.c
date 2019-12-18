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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  enum MessageType { ____Placeholder_MessageType } MessageType ;

/* Variables and functions */
 int GetLocalizedMessageOffset () ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  hDllInstance ; 

wchar_t *LoadMessageW(enum MessageType e){
	wchar_t *pTmp=(wchar_t*)calloc(sizeof(wchar_t),1024);
	LoadStringW(hDllInstance,GetLocalizedMessageOffset()+e,pTmp,1024);
	return pTmp;
}