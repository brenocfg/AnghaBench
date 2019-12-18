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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  jack_t ;

/* Variables and functions */
 int /*<<< orphan*/  write_buffer (int /*<<< orphan*/ *,float const*,size_t) ; 

__attribute__((used)) static ssize_t ja_write(void *data, const void *buf, size_t size)
{
   jack_t *jd = (jack_t*)data;

   return write_buffer(jd, (const float*)buf, size);
}