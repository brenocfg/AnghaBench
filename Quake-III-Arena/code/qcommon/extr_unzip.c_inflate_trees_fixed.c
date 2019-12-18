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
typedef  int /*<<< orphan*/  z_streamp ;
typedef  int /*<<< orphan*/  uInt ;
typedef  int /*<<< orphan*/  inflate_huft ;

/* Variables and functions */
 int Z_OK ; 
 int /*<<< orphan*/  fixed_bd ; 
 int /*<<< orphan*/  fixed_bl ; 
 int /*<<< orphan*/ * fixed_td ; 
 int /*<<< orphan*/ * fixed_tl ; 

int inflate_trees_fixed(uInt *bl, uInt *bd, inflate_huft * *tl, inflate_huft * *td, z_streamp z)
//uInt *bl;               /* literal desired/actual bit depth */
//uInt *bd;               /* distance desired/actual bit depth */
//inflate_huft * *tl;  /* literal/length tree result */
//inflate_huft * *td;  /* distance tree result */
//z_streamp z;             /* for memory allocation */
{
  *bl = fixed_bl;
  *bd = fixed_bd;
  *tl = fixed_tl;
  *td = fixed_td;
  return Z_OK;
}