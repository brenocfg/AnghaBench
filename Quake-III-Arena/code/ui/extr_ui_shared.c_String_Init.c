#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ getBindingBuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  Controls_GetConfig () ; 
 TYPE_1__* DC ; 
 int HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  Item_SetupKeywordHash () ; 
 int /*<<< orphan*/  Menu_SetupKeywordHash () ; 
 int /*<<< orphan*/  UI_InitMemory () ; 
 scalar_t__ menuCount ; 
 scalar_t__ openMenuCount ; 
 scalar_t__* strHandle ; 
 scalar_t__ strHandleCount ; 
 scalar_t__ strPoolIndex ; 

void String_Init() {
	int i;
	for (i = 0; i < HASH_TABLE_SIZE; i++) {
		strHandle[i] = 0;
	}
	strHandleCount = 0;
	strPoolIndex = 0;
	menuCount = 0;
	openMenuCount = 0;
	UI_InitMemory();
	Item_SetupKeywordHash();
	Menu_SetupKeywordHash();
	if (DC && DC->getBindingBuf) {
		Controls_GetConfig();
	}
}