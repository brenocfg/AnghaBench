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
typedef  TYPE_1__* plink_detect_t ;
typedef  int /*<<< orphan*/  link_detect_t ;
struct TYPE_4__ {int /*<<< orphan*/  SlotNum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SLOT_NUM ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8180_link_detect_init(plink_detect_t plink_detect)
{
	memset(plink_detect, 0, sizeof(link_detect_t));
	plink_detect->SlotNum = DEFAULT_SLOT_NUM;
}