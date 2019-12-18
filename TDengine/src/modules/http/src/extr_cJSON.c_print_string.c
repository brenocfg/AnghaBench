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
typedef  int /*<<< orphan*/  printbuffer ;
typedef  int /*<<< orphan*/  cJSON_bool ;
struct TYPE_3__ {scalar_t__ valuestring; } ;
typedef  TYPE_1__ cJSON ;

/* Variables and functions */
 int /*<<< orphan*/  print_string_ptr (unsigned char*,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static cJSON_bool print_string(const cJSON * const item, printbuffer * const p)
{
    return print_string_ptr((unsigned char*)item->valuestring, p);
}