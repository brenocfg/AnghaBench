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
struct connectdata {int dummy; } ;
typedef  int /*<<< orphan*/  contenc_writer ;

/* Variables and functions */

__attribute__((used)) static void identity_close_writer(struct connectdata *conn,
                                  contenc_writer *writer)
{
  (void) conn;
  (void) writer;
}