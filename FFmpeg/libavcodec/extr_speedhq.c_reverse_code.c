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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  reverse (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void reverse_code(const uint16_t *code, const uint8_t *bits,
                         uint16_t *reversed_code, int num_entries)
{
    int i;
    for (i = 0; i < num_entries; i++) {
        reversed_code[i] = reverse(code[i], bits[i]);
    }
}