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
struct rtx_iv {int dummy; } ;
struct biv_entry {struct rtx_iv iv; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bivs ; 
 struct biv_entry* htab_find_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
analyzed_for_bivness_p (rtx def, struct rtx_iv *iv)
{
  struct biv_entry *biv = htab_find_with_hash (bivs, def, REGNO (def));

  if (!biv)
    return false;

  *iv = biv->iv;
  return true;
}