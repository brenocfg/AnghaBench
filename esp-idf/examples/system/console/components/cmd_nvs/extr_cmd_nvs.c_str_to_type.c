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
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ type_str_pair_t ;
typedef  int /*<<< orphan*/  nvs_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVS_TYPE_ANY ; 
 int TYPE_STR_PAIR_SIZE ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* type_str_pair ; 

__attribute__((used)) static nvs_type_t str_to_type(const char *type)
{
    for (int i = 0; i < TYPE_STR_PAIR_SIZE; i++) {
        const type_str_pair_t *p = &type_str_pair[i];
        if (strcmp(type, p->str) == 0) {
            return  p->type;
        }
    }

    return NVS_TYPE_ANY;
}