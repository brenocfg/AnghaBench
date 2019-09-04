#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  r ;
typedef  int* qr_point ;
typedef  int* qr_line ;
typedef  int /*<<< orphan*/  qr_hom_cell ;
typedef  int /*<<< orphan*/  qr_hom ;
struct TYPE_20__ {int* size; int* o; int* ninliers; int* eversion; TYPE_2__** edge_pts; TYPE_1__* c; } ;
typedef  TYPE_3__ qr_finder ;
struct TYPE_21__ {int res; int x0; int y0; int** fwd; } ;
typedef  TYPE_4__ qr_aff ;
typedef  int /*<<< orphan*/  isaac_ctx ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_19__ {int /*<<< orphan*/  pos; } ;
struct TYPE_18__ {int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 int INT_MAX ; 
 scalar_t__ QR_DIVROUND (long long,long long) ; 
 long long QR_EXTMUL (int,int,long long) ; 
 int QR_FINDER_SUBPREC ; 
 int /*<<< orphan*/  QR_HOM_BITS ; 
 int QR_MAXI (int,int) ; 
 int QR_MINI (int,int) ; 
 long long QR_SIGNMASK (long long) ; 
 int abs (int) ; 
 int /*<<< orphan*/  free (int**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qr_aff_line_step (TYPE_4__ const*,int*,int,int,int*) ; 
 int /*<<< orphan*/  qr_aff_project (int*,TYPE_4__ const*,int,int) ; 
 int /*<<< orphan*/  qr_aff_unproject (int*,TYPE_4__ const*,int,int) ; 
 scalar_t__ qr_alignment_pattern_search (int*,int /*<<< orphan*/ *,int,int,int,unsigned char const*,int,int) ; 
 int qr_finder_locate_crossing (unsigned char const*,int,int,int,int,int,int,int,int*) ; 
 int qr_finder_quick_crossing_check (unsigned char const*,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  qr_finder_ransac (TYPE_3__*,TYPE_4__ const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qr_hom_cell_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  qr_hom_init (int /*<<< orphan*/ *,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int qr_ilog (int) ; 
 scalar_t__ qr_line_eval (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qr_line_fit_finder_edge (int*,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  qr_line_fit_finder_pair (int*,TYPE_4__ const*,TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  qr_line_fit_points (int*,int**,int,int) ; 
 scalar_t__ qr_line_isect (int*,int*,int*) ; 
 scalar_t__ realloc (int**,int) ; 

__attribute__((used)) static int qr_hom_fit(qr_hom *_hom,qr_finder *_ul,qr_finder *_ur,
 qr_finder *_dl,qr_point _p[4],const qr_aff *_aff,isaac_ctx *_isaac,
 const unsigned char *_img,int _width,int _height){
  qr_point *b;
  int       nb;
  int       cb;
  qr_point *r;
  int       nr;
  int       cr;
  qr_line   l[4];
  qr_point  q;
  qr_point  p;
  int       ox;
  int       oy;
  int       ru;
  int       rv;
  int       dru;
  int       drv;
  int       bu;
  int       bv;
  int       dbu;
  int       dbv;
  int       rx;
  int       ry;
  int       drxi;
  int       dryi;
  int       drxj;
  int       dryj;
  int       rdone;
  int       nrempty;
  int       rlastfit;
  int       bx;
  int       by;
  int       dbxi;
  int       dbyi;
  int       dbxj;
  int       dbyj;
  int       bdone;
  int       nbempty;
  int       blastfit;
  int       shift;
  int       round;
  int       version4;
  int       brx;
  int       bry;
  int       i;
  /*We attempt to correct large-scale perspective distortion by fitting lines
     to the edge of the code area.
    We could also look for an alignment pattern now, but that wouldn't work for
     version 1 codes, which have no alignment pattern.
    Even if the code is supposed to have one, there's go guarantee we'd find it
     intact.*/
  /*Fitting lines is easy for the edges on which we have two finder patterns.
    After the fit, UL is guaranteed to be on the proper side, but if either of
     the other two finder patterns aren't, something is wrong.*/
  qr_finder_ransac(_ul,_aff,_isaac,0);
  qr_finder_ransac(_dl,_aff,_isaac,0);
  qr_line_fit_finder_pair(l[0],_aff,_ul,_dl,0);
  if(qr_line_eval(l[0],_dl->c->pos[0],_dl->c->pos[1])<0||
   qr_line_eval(l[0],_ur->c->pos[0],_ur->c->pos[1])<0){
    return -1;
  }
  qr_finder_ransac(_ul,_aff,_isaac,2);
  qr_finder_ransac(_ur,_aff,_isaac,2);
  qr_line_fit_finder_pair(l[2],_aff,_ul,_ur,2);
  if(qr_line_eval(l[2],_dl->c->pos[0],_dl->c->pos[1])<0||
   qr_line_eval(l[2],_ur->c->pos[0],_ur->c->pos[1])<0){
    return -1;
  }
  /*The edges which only have one finder pattern are more difficult.
    We start by fitting a line to the edge of the one finder pattern we do
     have.
    This can fail due to an insufficient number of sample points, and even if
     it succeeds can be fairly inaccurate, because all of the points are
     clustered in one corner of the QR code.
    If it fails, we just use an axis-aligned line in the affine coordinate
     system.
    Then we walk along the edge of the entire code, looking for
     light:dark:light patterns perpendicular to the edge.
    Wherever we find one, we take the center of the dark portion as an
     additional sample point.
    At the end, we re-fit the line using all such sample points found.*/
  drv=_ur->size[1]>>1;
  qr_finder_ransac(_ur,_aff,_isaac,1);
  if(qr_line_fit_finder_edge(l[1],_ur,1,_aff->res)>=0){
    if(qr_line_eval(l[1],_ul->c->pos[0],_ul->c->pos[1])<0||
     qr_line_eval(l[1],_dl->c->pos[0],_dl->c->pos[1])<0){
      return -1;
    }
    /*Figure out the change in ru for a given change in rv when stepping along
       the fitted line.*/
    if(qr_aff_line_step(_aff,l[1],1,drv,&dru)<0)return -1;
  }
  else dru=0;
  ru=_ur->o[0]+3*_ur->size[0]-2*dru;
  rv=_ur->o[1]-2*drv;
  dbu=_dl->size[0]>>1;
  qr_finder_ransac(_dl,_aff,_isaac,3);
  if(qr_line_fit_finder_edge(l[3],_dl,3,_aff->res)>=0){
    if(qr_line_eval(l[3],_ul->c->pos[0],_ul->c->pos[1])<0||
     qr_line_eval(l[3],_ur->c->pos[0],_ur->c->pos[1])<0){
      return -1;
    }
    /*Figure out the change in bv for a given change in bu when stepping along
       the fitted line.*/
    if(qr_aff_line_step(_aff,l[3],0,dbu,&dbv)<0)return -1;
  }
  else dbv=0;
  bu=_dl->o[0]-2*dbu;
  bv=_dl->o[1]+3*_dl->size[1]-2*dbv;
  /*Set up the initial point lists.*/
  nr=rlastfit=_ur->ninliers[1];
  cr=nr+(_dl->o[1]-rv+drv-1)/drv;
  r=(qr_point *)malloc(cr*sizeof(*r));
  for(i=0;i<_ur->ninliers[1];i++){
    memcpy(r[i],_ur->edge_pts[1][i].pos,sizeof(r[i]));
  }
  nb=blastfit=_dl->ninliers[3];
  cb=nb+(_ur->o[0]-bu+dbu-1)/dbu;
  b=(qr_point *)malloc(cb*sizeof(*b));
  for(i=0;i<_dl->ninliers[3];i++){
    memcpy(b[i],_dl->edge_pts[3][i].pos,sizeof(b[i]));
  }
  /*Set up the step parameters for the affine projection.*/
  ox=(_aff->x0<<_aff->res)+(1<<_aff->res-1);
  oy=(_aff->y0<<_aff->res)+(1<<_aff->res-1);
  rx=_aff->fwd[0][0]*ru+_aff->fwd[0][1]*rv+ox;
  ry=_aff->fwd[1][0]*ru+_aff->fwd[1][1]*rv+oy;
  drxi=_aff->fwd[0][0]*dru+_aff->fwd[0][1]*drv;
  dryi=_aff->fwd[1][0]*dru+_aff->fwd[1][1]*drv;
  drxj=_aff->fwd[0][0]*_ur->size[0];
  dryj=_aff->fwd[1][0]*_ur->size[0];
  bx=_aff->fwd[0][0]*bu+_aff->fwd[0][1]*bv+ox;
  by=_aff->fwd[1][0]*bu+_aff->fwd[1][1]*bv+oy;
  dbxi=_aff->fwd[0][0]*dbu+_aff->fwd[0][1]*dbv;
  dbyi=_aff->fwd[1][0]*dbu+_aff->fwd[1][1]*dbv;
  dbxj=_aff->fwd[0][1]*_dl->size[1];
  dbyj=_aff->fwd[1][1]*_dl->size[1];
  /*Now step along the lines, looking for new sample points.*/
  nrempty=nbempty=0;
  for(;;){
    int ret;
    int x0;
    int y0;
    int x1;
    int y1;
    /*If we take too many steps without encountering a non-zero pixel, assume
       we have wandered off the edge and stop looking before we hit the other
       side of the quiet region.
      Otherwise, stop when the lines cross (if they do so inside the affine
       region) or come close to crossing (outside the affine region).
      TODO: We don't have any way of detecting when we've wandered into the
       code interior; we could stop if the outside sample ever shows up dark,
       but this could happen because of noise in the quiet region, too.*/
    rdone=rv>=QR_MINI(bv,_dl->o[1]+bv>>1)||nrempty>14;
    bdone=bu>=QR_MINI(ru,_ur->o[0]+ru>>1)||nbempty>14;
    if(!rdone&&(bdone||rv<bu)){
      x0=rx+drxj>>_aff->res+QR_FINDER_SUBPREC;
      y0=ry+dryj>>_aff->res+QR_FINDER_SUBPREC;
      x1=rx-drxj>>_aff->res+QR_FINDER_SUBPREC;
      y1=ry-dryj>>_aff->res+QR_FINDER_SUBPREC;
      if(nr>=cr){
        cr=cr<<1|1;
        r=(qr_point *)realloc(r,cr*sizeof(*r));
      }
      ret=qr_finder_quick_crossing_check(_img,_width,_height,x0,y0,x1,y1,1);
      if(!ret){
        ret=qr_finder_locate_crossing(_img,_width,_height,x0,y0,x1,y1,1,r[nr]);
      }
      if(ret>=0){
        if(!ret){
          qr_aff_unproject(q,_aff,r[nr][0],r[nr][1]);
          /*Move the current point halfway towards the crossing.
            We don't move the whole way to give us some robustness to noise.*/
          ru=ru+q[0]>>1;
          /*But ensure that rv monotonically increases.*/
          if(q[1]+drv>rv)rv=rv+q[1]>>1;
          rx=_aff->fwd[0][0]*ru+_aff->fwd[0][1]*rv+ox;
          ry=_aff->fwd[1][0]*ru+_aff->fwd[1][1]*rv+oy;
          nr++;
          /*Re-fit the line to update the step direction periodically.*/
          if(nr>QR_MAXI(1,rlastfit+(rlastfit>>2))){
            qr_line_fit_points(l[1],r,nr,_aff->res);
            if(qr_aff_line_step(_aff,l[1],1,drv,&dru)>=0){
              drxi=_aff->fwd[0][0]*dru+_aff->fwd[0][1]*drv;
              dryi=_aff->fwd[1][0]*dru+_aff->fwd[1][1]*drv;
            }
            rlastfit=nr;
          }
        }
        nrempty=0;
      }
      else nrempty++;
      ru+=dru;
      /*Our final defense: if we overflow, stop.*/
      if(rv+drv>rv)rv+=drv;
      else nrempty=INT_MAX;
      rx+=drxi;
      ry+=dryi;
    }
    else if(!bdone){
      x0=bx+dbxj>>_aff->res+QR_FINDER_SUBPREC;
      y0=by+dbyj>>_aff->res+QR_FINDER_SUBPREC;
      x1=bx-dbxj>>_aff->res+QR_FINDER_SUBPREC;
      y1=by-dbyj>>_aff->res+QR_FINDER_SUBPREC;
      if(nb>=cb){
        cb=cb<<1|1;
        b=(qr_point *)realloc(b,cb*sizeof(*b));
      }
      ret=qr_finder_quick_crossing_check(_img,_width,_height,x0,y0,x1,y1,1);
      if(!ret){
        ret=qr_finder_locate_crossing(_img,_width,_height,x0,y0,x1,y1,1,b[nb]);
      }
      if(ret>=0){
        if(!ret){
          qr_aff_unproject(q,_aff,b[nb][0],b[nb][1]);
          /*Move the current point halfway towards the crossing.
            We don't move the whole way to give us some robustness to noise.*/
          /*But ensure that bu monotonically increases.*/
          if(q[0]+dbu>bu)bu=bu+q[0]>>1;
          bv=bv+q[1]>>1;
          bx=_aff->fwd[0][0]*bu+_aff->fwd[0][1]*bv+ox;
          by=_aff->fwd[1][0]*bu+_aff->fwd[1][1]*bv+oy;
          nb++;
          /*Re-fit the line to update the step direction periodically.*/
          if(nb>QR_MAXI(1,blastfit+(blastfit>>2))){
            qr_line_fit_points(l[3],b,nb,_aff->res);
            if(qr_aff_line_step(_aff,l[3],0,dbu,&dbv)>=0){
              dbxi=_aff->fwd[0][0]*dbu+_aff->fwd[0][1]*dbv;
              dbyi=_aff->fwd[1][0]*dbu+_aff->fwd[1][1]*dbv;
            }
            blastfit=nb;
          }
        }
        nbempty=0;
      }
      else nbempty++;
      /*Our final defense: if we overflow, stop.*/
      if(bu+dbu>bu)bu+=dbu;
      else nbempty=INT_MAX;
      bv+=dbv;
      bx+=dbxi;
      by+=dbyi;
    }
    else break;
  }
  /*Fit the new lines.
    If we _still_ don't have enough sample points, then just use an
     axis-aligned line from the affine coordinate system (e.g., one parallel
     to the opposite edge in the image).*/
  if(nr>1)qr_line_fit_points(l[1],r,nr,_aff->res);
  else{
    qr_aff_project(p,_aff,_ur->o[0]+3*_ur->size[0],_ur->o[1]);
    shift=QR_MAXI(0,
     qr_ilog(QR_MAXI(abs(_aff->fwd[0][1]),abs(_aff->fwd[1][1])))
     -(_aff->res+1>>1));
    round=(1<<shift)>>1;
    l[1][0]=_aff->fwd[1][1]+round>>shift;
    l[1][1]=-_aff->fwd[0][1]+round>>shift;
    l[1][2]=-(l[1][0]*p[0]+l[1][1]*p[1]);
  }
  free(r);
  if(nb>1)qr_line_fit_points(l[3],b,nb,_aff->res);
  else{
    qr_aff_project(p,_aff,_dl->o[0],_dl->o[1]+3*_dl->size[1]);
    shift=QR_MAXI(0,
     qr_ilog(QR_MAXI(abs(_aff->fwd[0][1]),abs(_aff->fwd[1][1])))
     -(_aff->res+1>>1));
    round=(1<<shift)>>1;
    l[3][0]=_aff->fwd[1][0]+round>>shift;
    l[3][1]=-_aff->fwd[0][0]+round>>shift;
    l[3][2]=-(l[1][0]*p[0]+l[1][1]*p[1]);
  }
  free(b);
  for(i=0;i<4;i++){
    if(qr_line_isect(_p[i],l[i&1],l[2+(i>>1)])<0)return -1;
    /*It's plausible for points to be somewhat outside the image, but too far
       and too much of the pattern will be gone for it to be decodable.*/
    if(_p[i][0]<-_width<<QR_FINDER_SUBPREC||
     _p[i][0]>=_width<<QR_FINDER_SUBPREC+1||
     _p[i][1]<-_height<<QR_FINDER_SUBPREC||
     _p[i][1]>=_height<<QR_FINDER_SUBPREC+1){
      return -1;
    }
  }
  /*By default, use the edge intersection point for the bottom-right corner.*/
  brx=_p[3][0];
  bry=_p[3][1];
  /*However, if our average version estimate is greater than 1, NOW we try to
     search for an alignment pattern.
    We get a much better success rate by doing this after our initial attempt
     to promote the transform to a homography than before.
    You might also think it would be more reliable to use the interior finder
     pattern edges, since the outer ones may be obscured or damaged, and it
     would save us a reprojection below, since they would form a nice square
     with the location of the alignment pattern, but this turns out to be a bad
     idea.
    Non-linear distortion is usually maximal on the outside edge, and thus
     estimating the grid position from points on the interior means we might
     get mis-aligned by the time we reach the edge.*/
  version4=_ul->eversion[0]+_ul->eversion[1]+_ur->eversion[0]+_dl->eversion[1];
  if(version4>4){
    qr_hom_cell cell;
    qr_point    p3;
    int         dim;
    dim=17+version4;
    qr_hom_cell_init(&cell,0,0,dim-1,0,0,dim-1,dim-1,dim-1,
     _p[0][0],_p[0][1],_p[1][0],_p[1][1],
     _p[2][0],_p[2][1],_p[3][0],_p[3][1]);
    if(qr_alignment_pattern_search(p3,&cell,dim-7,dim-7,4,
     _img,_width,_height)>=0){
      long long w;
      long long mask;
      int       c21;
      int       dx21;
      int       dy21;
      /*There's no real need to update the bounding box corner, and in fact we
         actively perform worse if we do.
        Clearly it was good enough for us to find this alignment pattern, so
         it should be good enough to use for grid initialization.
        The point of doing the search was to get more accurate version
         estimates and a better chance of decoding the version and format info.
        This is particularly important for small versions that have no encoded
         version info, since any mismatch in version renders the code
         undecodable.*/
      /*We do, however, need four points in a square to initialize our
         homography, so project the point from the alignment center to the
         corner of the code area.*/
      c21=_p[2][0]*_p[1][1]-_p[2][1]*_p[1][0];
      dx21=_p[2][0]-_p[1][0];
      dy21=_p[2][1]-_p[1][1];
      w=QR_EXTMUL(dim-7,c21,
       QR_EXTMUL(dim-13,_p[0][0]*dy21-_p[0][1]*dx21,
       QR_EXTMUL(6,p3[0]*dy21-p3[1]*dx21,0)));
      /*The projection failed: invalid geometry.*/
      if(w==0)return -1;
      mask=QR_SIGNMASK(w);
      w=w+mask^mask;
      brx=(int)QR_DIVROUND(QR_EXTMUL((dim-7)*_p[0][0],p3[0]*dy21,
       QR_EXTMUL((dim-13)*p3[0],c21-_p[0][1]*dx21,
       QR_EXTMUL(6*_p[0][0],c21-p3[1]*dx21,0)))+mask^mask,w);
      bry=(int)QR_DIVROUND(QR_EXTMUL((dim-7)*_p[0][1],-p3[1]*dx21,
       QR_EXTMUL((dim-13)*p3[1],c21+_p[0][0]*dy21,
       QR_EXTMUL(6*_p[0][1],c21+p3[0]*dy21,0)))+mask^mask,w);
    }
  }
  /*Now we have four points that map to a square: initialize the projection.*/
  qr_hom_init(_hom,_p[0][0],_p[0][1],_p[1][0],_p[1][1],
   _p[2][0],_p[2][1],brx,bry,QR_HOM_BITS);
  return 0;
}