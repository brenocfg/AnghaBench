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
typedef  int /*<<< orphan*/  hb_value_array_t ;

/* Variables and functions */
 int MIN (int,size_t) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_array_get (int /*<<< orphan*/  const*,int) ; 
 size_t hb_value_array_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_value_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_array_clear (int /*<<< orphan*/ *) ; 

void
hb_value_array_copy(hb_value_array_t *dst,
                    const hb_value_array_t *src, int count)
{
    size_t len;
    int ii;

    // empty the first array if it is not already empty
    json_array_clear(dst);

    len = hb_value_array_len(src);
    count = MIN(count, len);
    for (ii = 0; ii < count; ii++)
        hb_value_array_append(dst, hb_value_dup(hb_value_array_get(src, ii)));
}