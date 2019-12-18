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
struct trans_stream_backend {int dummy; } ;

/* Variables and functions */
 struct trans_stream_backend const pipe_backend ; 

const struct trans_stream_backend* trans_stream_get_pipe_backend(void)
{
   return &pipe_backend;
}