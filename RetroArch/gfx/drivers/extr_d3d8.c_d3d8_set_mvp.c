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
struct d3d_matrix {int dummy; } ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE8 ;
typedef  int /*<<< orphan*/  D3DMATRIX ;

/* Variables and functions */
 int /*<<< orphan*/  D3DTS_PROJECTION ; 
 int /*<<< orphan*/  D3DTS_VIEW ; 
 int /*<<< orphan*/  D3DTS_WORLD ; 
 int /*<<< orphan*/  d3d8_set_transform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d_matrix_identity (struct d3d_matrix*) ; 
 int /*<<< orphan*/  d3d_matrix_transpose (struct d3d_matrix*,void const*) ; 

void d3d8_set_mvp(void *data, const void *mat_data)
{
   struct d3d_matrix matrix;
   LPDIRECT3DDEVICE8 d3dr     = (LPDIRECT3DDEVICE8)data;

   d3d_matrix_identity(&matrix);

   d3d8_set_transform(d3dr, D3DTS_PROJECTION, (D3DMATRIX*)&matrix);
   d3d8_set_transform(d3dr, D3DTS_VIEW, (D3DMATRIX*)&matrix);

   if (mat_data)
      d3d_matrix_transpose(&matrix, mat_data);

   d3d8_set_transform(d3dr, D3DTS_WORLD, (D3DMATRIX*)&matrix);
}