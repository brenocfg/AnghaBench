#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ncells; int* cell_limits; TYPE_2__** cells; } ;
typedef  TYPE_1__ qr_sampling_grid ;
typedef  int /*<<< orphan*/ * qr_point ;
struct TYPE_7__ {int u0; int v0; int** fwd; } ;
typedef  TYPE_2__ qr_hom_cell ;

/* Variables and functions */
 int QR_INT_BITS ; 
 int QR_INT_LOGBITS ; 
 int /*<<< orphan*/  SVG_ABS ; 
 int /*<<< orphan*/  qr_data_mask_fill (unsigned int*,int,int) ; 
 int /*<<< orphan*/  qr_hom_cell_fproject (int /*<<< orphan*/ *,TYPE_2__*,int,int,int) ; 
 int qr_img_get_bit (unsigned char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qr_sampling_grid_is_in_fp (TYPE_1__ const*,int,int,int) ; 
 int /*<<< orphan*/  svg_path_end () ; 
 int /*<<< orphan*/  svg_path_moveto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_path_start (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qr_sampling_grid_sample(const qr_sampling_grid *_grid,
 unsigned *_data_bits,int _dim,int _fmt_info,
 const unsigned char *_img,int _width,int _height){
  int stride;
  int u0;
  int u1;
  int j;
  /*We initialize the buffer with the data mask and XOR bits into it as we read
     them out of the image instead of unmasking in a separate step.*/
  qr_data_mask_fill(_data_bits,_dim,_fmt_info&7);
  stride=_dim+QR_INT_BITS-1>>QR_INT_LOGBITS;
  u0=0;
  svg_path_start("sampling-grid", 1, 0, 0);
  /*We read data cell-by-cell to avoid having to constantly change which
     projection we're using as we read each bit.
    This (and the position-dependent data mask) is the reason we buffer the
     bits we read instead of converting them directly to codewords here.
    Note that bits are stored column-wise, since that's how we'll scan them.*/
  for(j=0;j<_grid->ncells;j++){
    int i;
    int v0;
    int v1;
    u1=_grid->cell_limits[j];
    v0=0;
    for(i=0;i<_grid->ncells;i++){
      qr_hom_cell *cell;
      int          x0;
      int          y0;
      int          w0;
      int          u;
      int          du;
      int          dv;
      v1=_grid->cell_limits[i];
      cell=_grid->cells[i]+j;
      du=u0-cell->u0;
      dv=v0-cell->v0;
      x0=cell->fwd[0][0]*du+cell->fwd[0][1]*dv+cell->fwd[0][2];
      y0=cell->fwd[1][0]*du+cell->fwd[1][1]*dv+cell->fwd[1][2];
      w0=cell->fwd[2][0]*du+cell->fwd[2][1]*dv+cell->fwd[2][2];
      for(u=u0;u<u1;u++){
        int x;
        int y;
        int w;
        int v;
        x=x0;
        y=y0;
        w=w0;
        for(v=v0;v<v1;v++){
          /*Skip doing all the divisions and bounds checks if the bit is in the
             function pattern.*/
          if(!qr_sampling_grid_is_in_fp(_grid,_dim,u,v)){
            qr_point p;
            qr_hom_cell_fproject(p,cell,x,y,w);
            _data_bits[u*stride+(v>>QR_INT_LOGBITS)]^=
             qr_img_get_bit(_img,_width,_height,p[0],p[1])<<(v&QR_INT_BITS-1);
            svg_path_moveto(SVG_ABS, p[0], p[1]);
          }
          x+=cell->fwd[0][1];
          y+=cell->fwd[1][1];
          w+=cell->fwd[2][1];
        }
        x0+=cell->fwd[0][0];
        y0+=cell->fwd[1][0];
        w0+=cell->fwd[2][0];
      }
      v0=v1;
    }
    u0=u1;
  }
  svg_path_end();
}