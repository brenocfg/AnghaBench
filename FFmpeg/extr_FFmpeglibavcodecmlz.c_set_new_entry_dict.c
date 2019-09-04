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
struct TYPE_3__ {int parent_code; int string_code; int char_code; int match_len; } ;
typedef  TYPE_1__ MLZDict ;

/* Variables and functions */
 int FIRST_CODE ; 

__attribute__((used)) static void set_new_entry_dict(MLZDict* dict, int string_code, int parent_code, int char_code) {
    dict[string_code].parent_code = parent_code;
    dict[string_code].string_code = string_code;
    dict[string_code].char_code   = char_code;
    if (parent_code < FIRST_CODE) {
        dict[string_code].match_len = 2;
    } else {
        dict[string_code].match_len = (dict[parent_code].match_len) + 1;
    }
}