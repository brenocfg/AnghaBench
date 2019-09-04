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

/* Variables and functions */
 int QR_MAXI (int /*<<< orphan*/ ,int) ; 
 int QR_MINI (int,int) ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 scalar_t__ malloc (int) ; 

unsigned char *qr_binarize(const unsigned char *_img,int _width,int _height){
  unsigned char *mask = NULL;
  if(_width>0&&_height>0){
    unsigned      *col_sums;
    int            logwindw;
    int            logwindh;
    int            windw;
    int            windh;
    int            y0offs;
    int            y1offs;
    unsigned       g;
    int            x;
    int            y;
    mask=(unsigned char *)malloc(_width*_height*sizeof(*mask));
    /*We keep the window size fairly large to ensure it doesn't fit completely
       inside the center of a finder pattern of a version 1 QR code at full
       resolution.*/
    for(logwindw=4;logwindw<8&&(1<<logwindw)<(_width+7>>3);logwindw++);
    for(logwindh=4;logwindh<8&&(1<<logwindh)<(_height+7>>3);logwindh++);
    windw=1<<logwindw;
    windh=1<<logwindh;
    col_sums=(unsigned *)malloc(_width*sizeof(*col_sums));
    /*Initialize sums down each column.*/
    for(x=0;x<_width;x++){
      g=_img[x];
      col_sums[x]=(g<<logwindh-1)+g;
    }
    for(y=1;y<(windh>>1);y++){
      y1offs=QR_MINI(y,_height-1)*_width;
      for(x=0;x<_width;x++){
        g=_img[y1offs+x];
        col_sums[x]+=g;
      }
    }
    for(y=0;y<_height;y++){
      unsigned m;
      int      x0;
      int      x1;
      /*Initialize the sum over the window.*/
      m=(col_sums[0]<<logwindw-1)+col_sums[0];
      for(x=1;x<(windw>>1);x++){
        x1=QR_MINI(x,_width-1);
        m+=col_sums[x1];
      }
      for(x=0;x<_width;x++){
        /*Perform the test against the threshold T = (m/n)-D,
           where n=windw*windh and D=3.*/
        g=_img[y*_width+x];
        mask[y*_width+x]=-(g+3<<logwindw+logwindh<m)&0xFF;
        /*Update the window sum.*/
        if(x+1<_width){
          x0=QR_MAXI(0,x-(windw>>1));
          x1=QR_MINI(x+(windw>>1),_width-1);
          m+=col_sums[x1]-col_sums[x0];
        }
      }
      /*Update the column sums.*/
      if(y+1<_height){
        y0offs=QR_MAXI(0,y-(windh>>1))*_width;
        y1offs=QR_MINI(y+(windh>>1),_height-1)*_width;
        for(x=0;x<_width;x++){
          col_sums[x]-=_img[y0offs+x];
          col_sums[x]+=_img[y1offs+x];
        }
      }
    }
    free(col_sums);
  }
#if defined(QR_DEBUG)
  {
    FILE *fout;
    fout=fopen("binary.png","wb");
    image_write_png(_img,_width,_height,fout);
    fclose(fout);
  }
#endif
  return(mask);
}