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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 scalar_t__ TK_IMPORT ; 
 scalar_t__ TK_INSERT ; 
 TYPE_1__ tStrGetToken (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool tscIsInsertOrImportData(char* sqlstr) {
  int32_t index = 0;
  SSQLToken t0 = tStrGetToken(sqlstr, &index, false, 0, NULL);
  return t0.type == TK_INSERT || t0.type == TK_IMPORT;
}