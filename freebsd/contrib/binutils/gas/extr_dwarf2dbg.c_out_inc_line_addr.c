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
typedef  int /*<<< orphan*/  addressT ;

/* Variables and functions */
 int /*<<< orphan*/  emit_inc_line_addr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  frag_more (int) ; 
 int size_inc_line_addr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
out_inc_line_addr (int line_delta, addressT addr_delta)
{
  int len = size_inc_line_addr (line_delta, addr_delta);
  emit_inc_line_addr (line_delta, addr_delta, frag_more (len), len);
}