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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_IMAGPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REALPART (int /*<<< orphan*/ ) ; 
 int native_encode_expr (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
native_encode_complex (tree expr, unsigned char *ptr, int len)
{
  int rsize, isize;
  tree part;

  part = TREE_REALPART (expr);
  rsize = native_encode_expr (part, ptr, len);
  if (rsize == 0)
    return 0;
  part = TREE_IMAGPART (expr);
  isize = native_encode_expr (part, ptr+rsize, len-rsize);
  if (isize != rsize)
    return 0;
  return rsize + isize;
}