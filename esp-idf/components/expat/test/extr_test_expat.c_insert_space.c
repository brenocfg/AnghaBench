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
struct TYPE_3__ {int output_off; char* output; int depth; } ;
typedef  TYPE_1__ user_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void insert_space(user_data_t *user_data)
{
    const char align_str[] = "    ";

    TEST_ASSERT(sizeof(user_data->output) >= user_data->output_off);
    user_data->output[user_data->output_off++] = '\n';

    for (int i = 0; i < user_data->depth; i++) {
        for (int j = 0; j < strlen(align_str); ++j) {
            TEST_ASSERT(sizeof(user_data->output) >= user_data->output_off);
            user_data->output[user_data->output_off++] = align_str[j];
        }
    }
}