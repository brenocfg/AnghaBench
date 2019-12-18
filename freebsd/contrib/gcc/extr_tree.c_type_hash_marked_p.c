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
struct type_hash {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ TYPE_SYMTAB_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ ggc_marked_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
type_hash_marked_p (const void *p)
{
  tree type = ((struct type_hash *) p)->type;

  return ggc_marked_p (type) || TYPE_SYMTAB_POINTER (type);
}