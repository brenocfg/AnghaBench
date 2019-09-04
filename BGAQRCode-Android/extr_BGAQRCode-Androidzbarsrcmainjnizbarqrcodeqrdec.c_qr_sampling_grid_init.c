#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ncells; int** cells; unsigned int* fpmask; int* cell_limits; } ;
typedef  TYPE_1__ qr_sampling_grid ;
typedef  int* qr_point ;
typedef  int qr_hom_cell ;
typedef  int /*<<< orphan*/  base_cell ;

/* Variables and functions */
 int* QR_ALIGNMENT_SPACING ; 
 int QR_CLAMPI (int,int,int) ; 
 int QR_FINDER_SUBPREC ; 
 int QR_INT_BITS ; 
 int QR_INT_LOGBITS ; 
 int QR_MAXI (int /*<<< orphan*/ ,int) ; 
 int QR_MINI (int,int) ; 
 int /*<<< orphan*/  QR_SORT2I (int,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (int**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  qr_alignment_pattern_search (int*,int*,int,int,int,unsigned char const*,int,int) ; 
 int /*<<< orphan*/  qr_hom_cell_init (int*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  qr_hom_cell_project (int*,int*,int,int,int) ; 
 int /*<<< orphan*/  qr_sampling_grid_fp_mask_rect (TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  qr_svg_points (char*,int**,int) ; 

__attribute__((used)) static void qr_sampling_grid_init(qr_sampling_grid *_grid,int _version,
 const qr_point _ul_pos,const qr_point _ur_pos,const qr_point _dl_pos,
 qr_point _p[4],const unsigned char *_img,int _width,int _height){
  qr_hom_cell          base_cell;
  int                  align_pos[7];
  int                  dim;
  int                  nalign;
  int                  i;
  dim=17+(_version<<2);
  nalign=(_version/7)+2;
  /*Create a base cell to bootstrap the alignment pattern search.*/
  qr_hom_cell_init(&base_cell,0,0,dim-1,0,0,dim-1,dim-1,dim-1,
   _p[0][0],_p[0][1],_p[1][0],_p[1][1],_p[2][0],_p[2][1],_p[3][0],_p[3][1]);
  /*Allocate the array of cells.*/
  _grid->ncells=nalign-1;
  _grid->cells[0]=(qr_hom_cell *)malloc(
   (nalign-1)*(nalign-1)*sizeof(*_grid->cells[0]));
  for(i=1;i<_grid->ncells;i++)_grid->cells[i]=_grid->cells[i-1]+_grid->ncells;
  /*Initialize the function pattern mask.*/
  _grid->fpmask=(unsigned *)calloc(dim,
   (dim+QR_INT_BITS-1>>QR_INT_LOGBITS)*sizeof(*_grid->fpmask));
  /*Mask out the finder patterns (and separators and format info bits).*/
  qr_sampling_grid_fp_mask_rect(_grid,dim,0,0,9,9);
  qr_sampling_grid_fp_mask_rect(_grid,dim,0,dim-8,9,8);
  qr_sampling_grid_fp_mask_rect(_grid,dim,dim-8,0,8,9);
  /*Mask out the version number bits.*/
  if(_version>6){
    qr_sampling_grid_fp_mask_rect(_grid,dim,0,dim-11,6,3);
    qr_sampling_grid_fp_mask_rect(_grid,dim,dim-11,0,3,6);
  }
  /*Mask out the timing patterns.*/
  qr_sampling_grid_fp_mask_rect(_grid,dim,9,6,dim-17,1);
  qr_sampling_grid_fp_mask_rect(_grid,dim,6,9,1,dim-17);
  /*If we have no alignment patterns (e.g., this is a version 1 code), just use
     the base cell and hope it's good enough.*/
  if(_version<2)memcpy(_grid->cells[0],&base_cell,sizeof(base_cell));
  else{
    qr_point *q;
    qr_point *p;
    int       j;
    int       k;
    q=(qr_point *)malloc(nalign*nalign*sizeof(*q));
    p=(qr_point *)malloc(nalign*nalign*sizeof(*p));
    /*Initialize the alignment pattern position list.*/
    align_pos[0]=6;
    align_pos[nalign-1]=dim-7;
    if(_version>6){
      int d;
      d=QR_ALIGNMENT_SPACING[_version-7];
      for(i=nalign-1;i-->1;)align_pos[i]=align_pos[i+1]-d;
    }
    /*Three of the corners use a finder pattern instead of a separate
       alignment pattern.*/
    q[0][0]=3;
    q[0][1]=3;
    p[0][0]=_ul_pos[0];
    p[0][1]=_ul_pos[1];
    q[nalign-1][0]=dim-4;
    q[nalign-1][1]=3;
    p[nalign-1][0]=_ur_pos[0];
    p[nalign-1][1]=_ur_pos[1];
    q[(nalign-1)*nalign][0]=3;
    q[(nalign-1)*nalign][1]=dim-4;
    p[(nalign-1)*nalign][0]=_dl_pos[0];
    p[(nalign-1)*nalign][1]=_dl_pos[1];
    /*Scan for alignment patterns using a diagonal sweep.*/
    for(k=1;k<2*nalign-1;k++){
      int jmin;
      int jmax;
      jmax=QR_MINI(k,nalign-1)-(k==nalign-1);
      jmin=QR_MAXI(0,k-(nalign-1))+(k==nalign-1);
      for(j=jmin;j<=jmax;j++){
        qr_hom_cell *cell;
        int          u;
        int          v;
        int          k;
        i=jmax-(j-jmin);
        k=i*nalign+j;
        u=align_pos[j];
        v=align_pos[i];
        q[k][0]=u;
        q[k][1]=v;
        /*Mask out the alignment pattern.*/
        qr_sampling_grid_fp_mask_rect(_grid,dim,u-2,v-2,5,5);
        /*Pick a cell to use to govern the alignment pattern search.*/
        if(i>1&&j>1){
          qr_point p0;
          qr_point p1;
          qr_point p2;
          /*Each predictor is basically a straight-line extrapolation from two
             neighboring alignment patterns (except possibly near the opposing
             finder patterns).*/
          qr_hom_cell_project(p0,_grid->cells[i-2]+j-1,u,v,0);
          qr_hom_cell_project(p1,_grid->cells[i-2]+j-2,u,v,0);
          qr_hom_cell_project(p2,_grid->cells[i-1]+j-2,u,v,0);
          /*Take the median of the predictions as the search center.*/
          QR_SORT2I(p0[0],p1[0]);
          QR_SORT2I(p0[1],p1[1]);
          QR_SORT2I(p1[0],p2[0]);
          QR_SORT2I(p1[1],p2[1]);
          QR_SORT2I(p0[0],p1[0]);
          QR_SORT2I(p0[1],p1[1]);
          /*We need a cell that has the target point at a known (u,v) location.
            Since our cells don't have inverses, just construct one from our
             neighboring points.*/
          cell=_grid->cells[i-1]+j-1;
          qr_hom_cell_init(cell,
           q[k-nalign-1][0],q[k-nalign-1][1],q[k-nalign][0],q[k-nalign][1],
           q[k-1][0],q[k-1][1],q[k][0],q[k][1],
           p[k-nalign-1][0],p[k-nalign-1][1],p[k-nalign][0],p[k-nalign][1],
           p[k-1][0],p[k-1][1],p1[0],p1[1]);
        }
        else if(i>1&&j>0)cell=_grid->cells[i-2]+j-1;
        else if(i>0&&j>1)cell=_grid->cells[i-1]+j-2;
        else cell=&base_cell;
        /*Use a very small search radius.
          A large displacement here usually means a false positive (e.g., when
           the real alignment pattern is damaged or missing), which can
           severely distort the projection.*/
        qr_alignment_pattern_search(p[k],cell,u,v,2,_img,_width,_height);
        if(i>0&&j>0){
          qr_hom_cell_init(_grid->cells[i-1]+j-1,
           q[k-nalign-1][0],q[k-nalign-1][1],q[k-nalign][0],q[k-nalign][1],
           q[k-1][0],q[k-1][1],q[k][0],q[k][1],
           p[k-nalign-1][0],p[k-nalign-1][1],p[k-nalign][0],p[k-nalign][1],
           p[k-1][0],p[k-1][1],p[k][0],p[k][1]);
        }
      }
    }
    qr_svg_points("align", p, nalign * nalign);
    free(q);
    free(p);
  }
  /*Set the limits over which each cell is used.*/
  memcpy(_grid->cell_limits,align_pos+1,
   (_grid->ncells-1)*sizeof(*_grid->cell_limits));
  _grid->cell_limits[_grid->ncells-1]=dim;
  /*Produce a bounding square for the code (to mark finder centers with).
    Because of non-linear distortion, this might not actually bound the code,
     but it should be good enough.
    I don't think it's worth computing a convex hull or anything silly like
     that.*/
  qr_hom_cell_project(_p[0],_grid->cells[0]+0,-1,-1,1);
  qr_hom_cell_project(_p[1],_grid->cells[0]+_grid->ncells-1,(dim<<1)-1,-1,1);
  qr_hom_cell_project(_p[2],_grid->cells[_grid->ncells-1]+0,-1,(dim<<1)-1,1);
  qr_hom_cell_project(_p[3],_grid->cells[_grid->ncells-1]+_grid->ncells-1,
   (dim<<1)-1,(dim<<1)-1,1);
  /*Clamp the points somewhere near the image (this is really just in case a
     corner is near the plane at infinity).*/
  for(i=0;i<4;i++){
    _p[i][0]=QR_CLAMPI(-_width<<QR_FINDER_SUBPREC,_p[i][0],
     _width<<QR_FINDER_SUBPREC+1);
    _p[i][1]=QR_CLAMPI(-_height<<QR_FINDER_SUBPREC,_p[i][1],
     _height<<QR_FINDER_SUBPREC+1);
  }
  /*TODO: Make fine adjustments using the timing patterns.
    Possible strategy: scan the timing pattern at QR_ALIGN_SUBPREC (or finer)
     resolution, use dynamic programming to match midpoints between
     transitions to the ideal grid locations.*/
}