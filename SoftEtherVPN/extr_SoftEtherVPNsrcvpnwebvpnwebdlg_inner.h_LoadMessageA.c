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
typedef  enum MessageType { ____Placeholder_MessageType } MessageType ;

/* Variables and functions */
 int GetLocalizedMessageOffset () ; 
 int /*<<< orphan*/  LoadStringA (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  hDllInstance ; 

char *LoadMessageA(enum MessageType e){
	char *pTmp=(char*)calloc(sizeof(char),1024);
	LoadStringA(hDllInstance,GetLocalizedMessageOffset()+e,pTmp,1024);
	return pTmp;
}