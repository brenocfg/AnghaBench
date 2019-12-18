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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 

__attribute__((used)) static void __GX_SetTmemConfig(u8 nr)
{
	if(nr==0) {
		//  Set_TextureImage0-3, GXTexMapID=0-3 tmem_offset=00000000, cache_width=32 kb, cache_height=32 kb, image_type=cached
		GX_LOAD_BP_REG(0x8c0d8000);
		GX_LOAD_BP_REG(0x900dc000);
		GX_LOAD_BP_REG(0x8d0d8400);
		GX_LOAD_BP_REG(0x910dc400);
		GX_LOAD_BP_REG(0x8e0d8800);
		GX_LOAD_BP_REG(0x920dc800);
		GX_LOAD_BP_REG(0x8f0d8c00);
		GX_LOAD_BP_REG(0x930dcc00);

		//  Set_TextureImage0-3, GXTexMapID=4-7 tmem_offset=00010000, cache_width=32 kb, cache_height=32 kb, image_type=cached
		GX_LOAD_BP_REG(0xac0d9000);
		GX_LOAD_BP_REG(0xb00dd000);
		GX_LOAD_BP_REG(0xad0d9400);
		GX_LOAD_BP_REG(0xb10dd400);
		GX_LOAD_BP_REG(0xae0d9800);
		GX_LOAD_BP_REG(0xb20dd800);
		GX_LOAD_BP_REG(0xaf0d9c00);
		GX_LOAD_BP_REG(0xb30ddc00);

		return;
	}

	if(nr==1) {
		//  Set_TextureImage0-3, GXTexMapID=0-3 tmem_offset=00000000, cache_width=32 kb, cache_height=32 kb, image_type=cached
		GX_LOAD_BP_REG(0x8c0d8000);
		GX_LOAD_BP_REG(0x900dc000);
		GX_LOAD_BP_REG(0x8d0d8800);
		GX_LOAD_BP_REG(0x910dc800);
		GX_LOAD_BP_REG(0x8e0d9000);
		GX_LOAD_BP_REG(0x920dd000);
		GX_LOAD_BP_REG(0x8f0d9800);
		GX_LOAD_BP_REG(0x930dd800);

		//  Set_TextureImage0-3, GXTexMapID=4-7 tmem_offset=00010000, cache_width=32 kb, cache_height=32 kb, image_type=cached
		GX_LOAD_BP_REG(0xac0da000);
		GX_LOAD_BP_REG(0xb00de000);
		GX_LOAD_BP_REG(0xad0da800);
		GX_LOAD_BP_REG(0xb10de800);
		GX_LOAD_BP_REG(0xae0db000);
		GX_LOAD_BP_REG(0xb20df000);
		GX_LOAD_BP_REG(0xaf0db800);
		GX_LOAD_BP_REG(0xb30df800);

		return;
	}

	if(nr==2) {
		//  Set_TextureImage0-3, GXTexMapID=0-3 tmem_offset=00000000, cache_width=32 kb, cache_height=32 kb, image_type=cached
		GX_LOAD_BP_REG(0x8c0d8000);
		GX_LOAD_BP_REG(0x900dc000);
		GX_LOAD_BP_REG(0x8d0d8800);
		GX_LOAD_BP_REG(0x910dc800);
		GX_LOAD_BP_REG(0x8e0d9000);
		GX_LOAD_BP_REG(0x920dd000);
		GX_LOAD_BP_REG(0x8f0d9800);
		GX_LOAD_BP_REG(0x930dd800);

		//  Set_TextureImage0-3, GXTexMapID=4-7 tmem_offset=00010000, cache_width=32 kb, cache_height=32 kb, image_type=cached
		GX_LOAD_BP_REG(0xac0da000);
		GX_LOAD_BP_REG(0xb00dc400);
		GX_LOAD_BP_REG(0xad0da800);
		GX_LOAD_BP_REG(0xb10dcc00);
		GX_LOAD_BP_REG(0xae0db000);
		GX_LOAD_BP_REG(0xb20dd400);
		GX_LOAD_BP_REG(0xaf0db800);
		GX_LOAD_BP_REG(0xb30ddc00);

		return;
	}
}