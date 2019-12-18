#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  chain; } ;
typedef  TYPE_1__ hlsl_renderchain_t ;
typedef  int /*<<< orphan*/  d3d9_renderchain_t ;

/* Variables and functions */
 int d3d9_renderchain_add_lut (int /*<<< orphan*/ *,char const*,char const*,int) ; 

__attribute__((used)) static bool hlsl_d3d9_renderchain_add_lut(void *data,
      const char *id, const char *path, bool smooth)
{
   hlsl_renderchain_t *_chain  = (hlsl_renderchain_t*)data;
   d3d9_renderchain_t *chain   = (d3d9_renderchain_t*)&_chain->chain;

   return d3d9_renderchain_add_lut(chain, id, path, smooth);
}