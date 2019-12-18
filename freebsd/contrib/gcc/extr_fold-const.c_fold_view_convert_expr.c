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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int CHAR_BIT ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int native_encode_expr (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  native_interpret_expr (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static tree
fold_view_convert_expr (tree type, tree expr)
{
  /* We support up to 512-bit values (for V8DFmode).  */
  unsigned char buffer[64];
  int len;

  /* Check that the host and target are sane.  */
  if (CHAR_BIT != 8 || BITS_PER_UNIT != 8)
    return NULL_TREE;

  len = native_encode_expr (expr, buffer, sizeof (buffer));
  if (len == 0)
    return NULL_TREE;

  return native_interpret_expr (type, buffer, len);
}