#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kiss_fftnd_cfg ;
typedef  int /*<<< orphan*/  const kiss_fft_cpx ;
struct TYPE_3__ {int ndims; int dimprod; int* dims; int /*<<< orphan*/  const* tmpbuf; int /*<<< orphan*/ * states; } ;

/* Variables and functions */
 int /*<<< orphan*/  kiss_fft_stride (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

void kiss_fftnd(kiss_fftnd_cfg st,const kiss_fft_cpx *fin,kiss_fft_cpx *fout)
{
    int i,k;
    const kiss_fft_cpx * bufin=fin;
    kiss_fft_cpx * bufout;

    /*arrange it so the last bufout == fout*/
    if ( st->ndims & 1 ) {
        bufout = fout;
        if (fin==fout) {
            memcpy( st->tmpbuf, fin, sizeof(kiss_fft_cpx) * st->dimprod );
            bufin = st->tmpbuf;
        }
    }else
        bufout = st->tmpbuf;

    for ( k=0; k < st->ndims; ++k) {
        int curdim = st->dims[k];
        int stride = st->dimprod / curdim;

        for ( i=0 ; i<stride ; ++i ) 
            kiss_fft_stride( st->states[k], bufin+i , bufout+i*curdim, stride );

        /*toggle back and forth between the two buffers*/
        if (bufout == st->tmpbuf){
            bufout = fout;
            bufin = st->tmpbuf;
        }else{
            bufout = st->tmpbuf;
            bufin = fout;
        }
    }
}