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
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  schemas; } ;
typedef  int /*<<< orphan*/  STgSchema ;

/* Variables and functions */
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  tgFreeSchemas () ; 
 TYPE_1__ tgSchemas ; 

void tgInitSchemas(int size) {
  tgFreeSchemas();
  tgSchemas.schemas = calloc(sizeof(STgSchema), size);
  tgSchemas.size = 0;
}