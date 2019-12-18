#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
typedef  scalar_t__ uInt ;
typedef  int /*<<< orphan*/  inflate_huft ;
struct TYPE_5__ {char* msg; } ;

/* Variables and functions */
 scalar_t__ ZALLOC (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ZFREE (TYPE_1__*,scalar_t__*) ; 
 int Z_BUF_ERROR ; 
 int Z_DATA_ERROR ; 
 int Z_MEM_ERROR ; 
 scalar_t__* Z_NULL ; 
 int huft_build (scalar_t__*,int,int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

int inflate_trees_bits(uInt *c, uInt *bb, inflate_huft * *tb, inflate_huft *hp, z_streamp z)
//uInt *c;               /* 19 code lengths */
//uInt *bb;              /* bits tree desired/actual depth */
//inflate_huft * *tb; /* bits tree result */
//inflate_huft *hp;       /* space for trees */
//z_streamp z;            /* for messages */
{
  int r;
  uInt hn = 0;          /* hufts used in space */
  uInt *v;             /* work area for huft_build */

  if ((v = (uInt*)ZALLOC(z, 19, sizeof(uInt))) == Z_NULL)
    return Z_MEM_ERROR;
  r = huft_build(c, 19, 19, (uInt*)Z_NULL, (uInt*)Z_NULL,
                 tb, bb, hp, &hn, v);
  if (r == Z_DATA_ERROR)
    z->msg = (char*)"oversubscribed dynamic bit lengths tree";
  else if (r == Z_BUF_ERROR || *bb == 0)
  {
    z->msg = (char*)"incomplete dynamic bit lengths tree";
    r = Z_DATA_ERROR;
  }
  ZFREE(z, v);
  return r;
}