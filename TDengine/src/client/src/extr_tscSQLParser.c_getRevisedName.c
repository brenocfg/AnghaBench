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
typedef  size_t int32_t ;
struct TYPE_2__ {char* aName; } ;

/* Variables and functions */
 TYPE_1__* aAggs ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 

void getRevisedName(char* resultFieldName, int32_t functionId, int32_t maxLen, char* columnName) {
  snprintf(resultFieldName, maxLen, "%s(%s)", aAggs[functionId].aName, columnName);
}