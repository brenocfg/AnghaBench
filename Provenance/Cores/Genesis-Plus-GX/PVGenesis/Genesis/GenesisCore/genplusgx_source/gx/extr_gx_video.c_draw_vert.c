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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  f32 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_Position1x8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_TexCoord2f32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void draw_vert(u8 pos, f32 s, f32 t)
{
  GX_Position1x8(pos);
  GX_TexCoord2f32(s, t);
}