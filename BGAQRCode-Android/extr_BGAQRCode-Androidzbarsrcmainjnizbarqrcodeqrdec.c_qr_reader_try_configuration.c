#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  gf; int /*<<< orphan*/  isaac; } ;
typedef  TYPE_1__ qr_reader ;
typedef  int* qr_point ;
struct TYPE_26__ {int** inv; int** fwd; } ;
typedef  TYPE_2__ qr_hom ;
struct TYPE_27__ {int /*<<< orphan*/ * pos; } ;
typedef  TYPE_3__ qr_finder_center ;
struct TYPE_28__ {int* o; int* eversion; int* size; TYPE_3__* c; } ;
typedef  TYPE_4__ qr_finder ;
struct TYPE_29__ {int /*<<< orphan*/  bbox; } ;
typedef  TYPE_5__ qr_code_data ;
typedef  int /*<<< orphan*/  qr_aff ;
typedef  int /*<<< orphan*/  bbox ;

/* Variables and functions */
 int QR_FINDER_SUBPREC ; 
 int QR_INT_BITS ; 
 int QR_LARGE_VERSION_SLACK ; 
 scalar_t__ QR_MAXI (int,int) ; 
 int QR_SMALL_VERSION_SLACK ; 
 int /*<<< orphan*/  QR_SWAP2I (int,int) ; 
 int abs (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int**,int) ; 
 int /*<<< orphan*/  qr_aff_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qr_aff_unproject (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qr_code_decode (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,unsigned char const*,int,int) ; 
 int /*<<< orphan*/  qr_finder_edge_pts_aff_classify (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qr_finder_edge_pts_hom_classify (TYPE_4__*,TYPE_2__*) ; 
 scalar_t__ qr_finder_estimate_module_size_and_version (TYPE_4__*,int,int) ; 
 int qr_finder_fmt_info_decode (TYPE_4__*,TYPE_4__*,TYPE_4__*,TYPE_2__*,unsigned char const*,int,int) ; 
 int qr_finder_version_decode (TYPE_4__*,TYPE_2__*,unsigned char const*,int,int,int) ; 
 scalar_t__ qr_hom_fit (TYPE_2__*,TYPE_4__*,TYPE_4__*,TYPE_4__*,int**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,int,int) ; 
 int /*<<< orphan*/  qr_hom_unproject (int*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qr_ilog (scalar_t__) ; 
 int qr_point_ccw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int qr_point_distance2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qr_reader_try_configuration(qr_reader *_reader,
 qr_code_data *_qrdata,const unsigned char *_img,int _width,int _height,
 qr_finder_center *_c[3]){
  int      ci[7];
  unsigned maxd;
  int      ccw;
  int      i0;
  int      i;
  /*Sort the points in counter-clockwise order.*/
  ccw=qr_point_ccw(_c[0]->pos,_c[1]->pos,_c[2]->pos);
  /*Colinear points can't be the corners of a quadrilateral.*/
  if(!ccw)return -1;
  /*Include a few extra copies of the cyclical list to avoid mods.*/
  ci[6]=ci[3]=ci[0]=0;
  ci[4]=ci[1]=1+(ccw<0);
  ci[5]=ci[2]=2-(ccw<0);
  /*Assume the points farthest from each other are the opposite corners, and
     find the top-left point.*/
  maxd=qr_point_distance2(_c[1]->pos,_c[2]->pos);
  i0=0;
  for(i=1;i<3;i++){
    unsigned d;
    d=qr_point_distance2(_c[ci[i+1]]->pos,_c[ci[i+2]]->pos);
    if(d>maxd){
      i0=i;
      maxd=d;
    }
  }
  /*However, try all three possible orderings, just to be sure (a severely
     skewed projection could move opposite corners closer than adjacent).*/
  for(i=i0;i<i0+3;i++){
    qr_aff    aff;
    qr_hom    hom;
    qr_finder ul;
    qr_finder ur;
    qr_finder dl;
    qr_point  bbox[4];
    int       res;
    int       ur_version;
    int       dl_version;
    int       fmt_info;
    ul.c=_c[ci[i]];
    ur.c=_c[ci[i+1]];
    dl.c=_c[ci[i+2]];
    /*Estimate the module size and version number from the two opposite corners.
      The module size is not constant in the image, so we compute an affine
       projection from the three points we have to a square domain, and
       estimate it there.
      Although it should be the same along both axes, we keep separate
       estimates to account for any remaining projective distortion.*/
    res=QR_INT_BITS-2-QR_FINDER_SUBPREC-qr_ilog(QR_MAXI(_width,_height)-1);
    qr_aff_init(&aff,ul.c->pos,ur.c->pos,dl.c->pos,res);
    qr_aff_unproject(ur.o,&aff,ur.c->pos[0],ur.c->pos[1]);
    qr_finder_edge_pts_aff_classify(&ur,&aff);
    if(qr_finder_estimate_module_size_and_version(&ur,1<<res,1<<res)<0)continue;
    qr_aff_unproject(dl.o,&aff,dl.c->pos[0],dl.c->pos[1]);
    qr_finder_edge_pts_aff_classify(&dl,&aff);
    if(qr_finder_estimate_module_size_and_version(&dl,1<<res,1<<res)<0)continue;
    /*If the estimated versions are significantly different, reject the
       configuration.*/
    if(abs(ur.eversion[1]-dl.eversion[0])>QR_LARGE_VERSION_SLACK)continue;
    qr_aff_unproject(ul.o,&aff,ul.c->pos[0],ul.c->pos[1]);
    qr_finder_edge_pts_aff_classify(&ul,&aff);
    if(qr_finder_estimate_module_size_and_version(&ul,1<<res,1<<res)<0||
     abs(ul.eversion[1]-ur.eversion[1])>QR_LARGE_VERSION_SLACK||
     abs(ul.eversion[0]-dl.eversion[0])>QR_LARGE_VERSION_SLACK){
      continue;
    }
#if defined(QR_DEBUG)
    qr_finder_dump_aff_undistorted(&ul,&ur,&dl,&aff,_img,_width,_height);
#endif
    /*If we made it this far, upgrade the affine homography to a full
       homography.*/
    if(qr_hom_fit(&hom,&ul,&ur,&dl,bbox,&aff,
     &_reader->isaac,_img,_width,_height)<0){
      continue;
    }
    memcpy(_qrdata->bbox,bbox,sizeof(bbox));
    qr_hom_unproject(ul.o,&hom,ul.c->pos[0],ul.c->pos[1]);
    qr_hom_unproject(ur.o,&hom,ur.c->pos[0],ur.c->pos[1]);
    qr_hom_unproject(dl.o,&hom,dl.c->pos[0],dl.c->pos[1]);
    qr_finder_edge_pts_hom_classify(&ur,&hom);
    if(qr_finder_estimate_module_size_and_version(&ur,
     ur.o[0]-ul.o[0],ur.o[0]-ul.o[0])<0){
      continue;
    }
    qr_finder_edge_pts_hom_classify(&dl,&hom);
    if(qr_finder_estimate_module_size_and_version(&dl,
     dl.o[1]-ul.o[1],dl.o[1]-ul.o[1])<0){
      continue;
    }
#if defined(QR_DEBUG)
    qr_finder_dump_hom_undistorted(&ul,&ur,&dl,&hom,_img,_width,_height);
#endif
    /*If we have a small version (less than 7), there's no encoded version
       information.
      If the estimated version on the two corners matches and is sufficiently
       small, we assume this is the case.*/
    if(ur.eversion[1]==dl.eversion[0]&&ur.eversion[1]<7){
      /*We used to do a whole bunch of extra geometric checks for small
         versions, because with just an affine correction, it was fairly easy
         to estimate two consistent module sizes given a random configuration.
        However, now that we're estimating a full homography, these appear to
         be unnecessary.*/
#if 0
      static const signed char LINE_TESTS[12][6]={
        /*DL left, UL > 0, UR > 0*/
        {2,0,0, 1,1, 1},
        /*DL right, UL > 0, UR < 0*/
        {2,1,0, 1,1,-1},
        /*UR top, UL > 0, DL > 0*/
        {1,2,0, 1,2, 1},
        /*UR bottom, UL > 0, DL < 0*/
        {1,3,0, 1,2,-1},
        /*UR left, DL < 0, UL < 0*/
        {1,0,2,-1,0,-1},
        /*UR right, DL > 0, UL > 0*/
        {1,1,2, 1,0, 1},
        /*DL top, UR < 0, UL < 0*/
        {2,2,1,-1,0,-1},
        /*DL bottom, UR > 0, UL > 0*/
        {2,3,1, 1,0, 1},
        /*UL left, DL > 0, UR > 0*/
        {0,0,2, 1,1, 1},
        /*UL right, DL > 0, UR < 0*/
        {0,1,2, 1,1,-1},
        /*UL top, UR > 0, DL > 0*/
        {0,2,1, 1,2, 1},
        /*UL bottom, UR > 0, DL < 0*/
        {0,3,1, 1,2,-1}
      };
      qr_finder *f[3];
      int        j;
      /*Start by decoding the format information.
        This is cheap, but unlikely to reject invalid configurations.
        56.25% of all bitstrings are valid, and we mix and match several pieces
         until we find a valid combination, so our real chances of finding a
         valid codeword in random bits are even higher.*/
      fmt_info=qr_finder_fmt_info_decode(&ul,&ur,&dl,&aff,_img,_width,_height);
      if(fmt_info<0)continue;
      /*Now we fit lines to the edges of each finder pattern and check to make
         sure the centers of the other finder patterns lie on the proper side.*/
      f[0]=&ul;
      f[1]=&ur;
      f[2]=&dl;
      for(j=0;j<12;j++){
        const signed char *t;
        qr_line            l0;
        int               *p;
        t=LINE_TESTS[j];
        qr_finder_ransac(f[t[0]],&aff,&_reader->isaac,t[1]);
        /*We may not have enough points to fit a line accurately here.
          If not, we just skip the test.*/
        if(qr_line_fit_finder_edge(l0,f[t[0]],t[1],res)<0)continue;
        p=f[t[2]]->c->pos;
        if(qr_line_eval(l0,p[0],p[1])*t[3]<0)break;
        p=f[t[4]]->c->pos;
        if(qr_line_eval(l0,p[0],p[1])*t[5]<0)break;
      }
      if(j<12)continue;
      /*All tests passed.*/
#endif
      ur_version=ur.eversion[1];
    }
    else{
      /*If the estimated versions are significantly different, reject the
         configuration.*/
      if(abs(ur.eversion[1]-dl.eversion[0])>QR_LARGE_VERSION_SLACK)continue;
      /*Otherwise we try to read the actual version data from the image.
        If the real version is not sufficiently close to our estimated version,
         then we assume there was an unrecoverable decoding error (so many bit
         errors we were within 3 errors of another valid code), and throw that
         value away.
        If no decoded version could be sufficiently close, we don't even try.*/
      if(ur.eversion[1]>=7-QR_LARGE_VERSION_SLACK){
        ur_version=qr_finder_version_decode(&ur,&hom,_img,_width,_height,0);
        if(abs(ur_version-ur.eversion[1])>QR_LARGE_VERSION_SLACK)ur_version=-1;
      }
      else ur_version=-1;
      if(dl.eversion[0]>=7-QR_LARGE_VERSION_SLACK){
        dl_version=qr_finder_version_decode(&dl,&hom,_img,_width,_height,1);
        if(abs(dl_version-dl.eversion[0])>QR_LARGE_VERSION_SLACK)dl_version=-1;
      }
      else dl_version=-1;
      /*If we got at least one valid version, or we got two and they match,
         then we found a valid configuration.*/
      if(ur_version>=0){
        if(dl_version>=0&&dl_version!=ur_version)continue;
      }
      else if(dl_version<0)continue;
      else ur_version=dl_version;
    }
    qr_finder_edge_pts_hom_classify(&ul,&hom);
    if(qr_finder_estimate_module_size_and_version(&ul,
     ur.o[0]-dl.o[0],dl.o[1]-ul.o[1])<0||
     abs(ul.eversion[1]-ur.eversion[1])>QR_SMALL_VERSION_SLACK||
     abs(ul.eversion[0]-dl.eversion[0])>QR_SMALL_VERSION_SLACK){
      continue;
    }
    fmt_info=qr_finder_fmt_info_decode(&ul,&ur,&dl,&hom,_img,_width,_height);
    if(fmt_info<0||
     qr_code_decode(_qrdata,&_reader->gf,ul.c->pos,ur.c->pos,dl.c->pos,
     ur_version,fmt_info,_img,_width,_height)<0){
      /*The code may be flipped.
        Try again, swapping the UR and DL centers.
        We should get a valid version either way, so it's relatively cheap to
         check this, as we've already filtered out a lot of invalid
         configurations.*/
      QR_SWAP2I(hom.inv[0][0],hom.inv[1][0]);
      QR_SWAP2I(hom.inv[0][1],hom.inv[1][1]);
      QR_SWAP2I(hom.fwd[0][0],hom.fwd[0][1]);
      QR_SWAP2I(hom.fwd[1][0],hom.fwd[1][1]);
      QR_SWAP2I(hom.fwd[2][0],hom.fwd[2][1]);
      QR_SWAP2I(ul.o[0],ul.o[1]);
      QR_SWAP2I(ul.size[0],ul.size[1]);
      QR_SWAP2I(ur.o[0],ur.o[1]);
      QR_SWAP2I(ur.size[0],ur.size[1]);
      QR_SWAP2I(dl.o[0],dl.o[1]);
      QR_SWAP2I(dl.size[0],dl.size[1]);
#if defined(QR_DEBUG)
      qr_finder_dump_hom_undistorted(&ul,&dl,&ur,&hom,_img,_width,_height);
#endif
      fmt_info=qr_finder_fmt_info_decode(&ul,&dl,&ur,&hom,_img,_width,_height);
      if(fmt_info<0)continue;
      QR_SWAP2I(bbox[1][0],bbox[2][0]);
      QR_SWAP2I(bbox[1][1],bbox[2][1]);
      memcpy(_qrdata->bbox,bbox,sizeof(bbox));
      if(qr_code_decode(_qrdata,&_reader->gf,ul.c->pos,dl.c->pos,ur.c->pos,
       ur_version,fmt_info,_img,_width,_height)<0){
        continue;
      }
    }
    return ur_version;
  }
  return -1;
}