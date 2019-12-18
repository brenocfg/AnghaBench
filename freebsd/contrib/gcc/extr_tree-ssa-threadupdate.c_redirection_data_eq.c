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
struct redirection_data {scalar_t__ outgoing_edge; } ;
typedef  scalar_t__ edge ;

/* Variables and functions */

__attribute__((used)) static int
redirection_data_eq (const void *p1, const void *p2)
{
  edge e1 = ((struct redirection_data *)p1)->outgoing_edge;
  edge e2 = ((struct redirection_data *)p2)->outgoing_edge;

  return e1 == e2;
}