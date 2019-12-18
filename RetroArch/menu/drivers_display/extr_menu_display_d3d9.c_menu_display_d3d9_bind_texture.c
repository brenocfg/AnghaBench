#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ texture; } ;
typedef  TYPE_1__ menu_display_ctx_draw_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ d3d9_video_t ;
typedef  int /*<<< orphan*/  LPDIRECT3DTEXTURE9 ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9 ;

/* Variables and functions */
 int /*<<< orphan*/  D3DTADDRESS_COMM_CLAMP ; 
 int /*<<< orphan*/  D3DTEXF_COMM_LINEAR ; 
 int /*<<< orphan*/  d3d9_set_sampler_address_u (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_sampler_address_v (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_sampler_magfilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_sampler_minfilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_sampler_mipfilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void menu_display_d3d9_bind_texture(menu_display_ctx_draw_t *draw,
      d3d9_video_t *d3d)
{
   LPDIRECT3DDEVICE9 dev = d3d->dev;

   d3d9_set_texture(dev, 0, (LPDIRECT3DTEXTURE9)draw->texture);
   d3d9_set_sampler_address_u(dev, 0, D3DTADDRESS_COMM_CLAMP);
   d3d9_set_sampler_address_v(dev, 0, D3DTADDRESS_COMM_CLAMP);
   d3d9_set_sampler_minfilter(dev, 0, D3DTEXF_COMM_LINEAR);
   d3d9_set_sampler_magfilter(dev, 0, D3DTEXF_COMM_LINEAR);
   d3d9_set_sampler_mipfilter(dev, 0, D3DTEXF_COMM_LINEAR);
}