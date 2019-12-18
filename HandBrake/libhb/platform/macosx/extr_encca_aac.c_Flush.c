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
typedef  int /*<<< orphan*/  hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 int /*<<< orphan*/ * Encode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Flush(hb_work_object_t *w, hb_buffer_list_t * list)
{
    hb_buffer_t *buf = Encode(w);
    while (buf)
    {
        hb_buffer_list_append(list, buf);
        buf = Encode(w);
    }
}