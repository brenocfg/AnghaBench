#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zfree; scalar_t__ opaque; int /*<<< orphan*/  zalloc; } ;
typedef  TYPE_1__ z_stream ;
typedef  scalar_t__ voidpf ;
typedef  int uInt ;
typedef  int /*<<< orphan*/  inflate_huft ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int inflate_trees_fixed (int*,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  maketree (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zcalloc ; 
 int /*<<< orphan*/  zcfree ; 

void main(void)
{
  int r;
  uInt bl, bd;
  inflate_huft *tl, *td;
  z_stream z;

  z.zalloc = zcalloc;
  z.opaque = (voidpf)0;
  z.zfree = zcfree;
  r = inflate_trees_fixed(&bl, &bd, &tl, &td, &z);
  if (r)
  {
    fprintf(stderr, "inflate_trees_fixed error %d\n", r);
    return;
  }
  puts("/* inffixed.h -- table for decoding fixed codes");
  puts(" * Generated automatically by the maketree.c program");
  puts(" */");
  puts("");
  puts("/* WARNING: this file should *not* be used by applications. It is");
  puts("   part of the implementation of the compression library and is");
  puts("   subject to change. Applications should only use zlib.h.");
  puts(" */");
  puts("");
  printf("local uInt fixed_bl = %d;\n", bl);
  printf("local uInt fixed_bd = %d;\n", bd);
  printf("local inflate_huft fixed_tl[] = {");
  maketree(bl, tl);
  puts("  };");
  printf("local inflate_huft fixed_td[] = {");
  maketree(bd, td);
  puts("  };");
}