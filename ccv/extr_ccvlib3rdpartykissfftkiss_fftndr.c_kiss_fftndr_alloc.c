#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kiss_fftndr_state {int dummy; } ;
typedef  TYPE_1__* kiss_fftndr_cfg ;
typedef  int /*<<< orphan*/  kiss_fft_scalar ;
struct TYPE_5__ {int dimReal; int dimOther; char* tmpbuf; scalar_t__ cfg_nd; scalar_t__ cfg_r; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 scalar_t__ kiss_fftnd_alloc (int const*,int,int,char*,size_t*) ; 
 scalar_t__ kiss_fftr_alloc (int,int,TYPE_1__*,size_t*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int prod (int const*,int) ; 

kiss_fftndr_cfg kiss_fftndr_alloc(const int *dims,int ndims,int inverse_fft,void*mem,size_t*lenmem)
{
    kiss_fftndr_cfg st = NULL;
    size_t nr=0 , nd=0,ntmp=0;
    int dimReal = dims[ndims-1];
    int dimOther = prod(dims,ndims-1);
    size_t memneeded;
    
    (void)kiss_fftr_alloc(dimReal,inverse_fft,NULL,&nr);
    (void)kiss_fftnd_alloc(dims,ndims-1,inverse_fft,NULL,&nd);
    ntmp =
        MAX( 2*dimOther , dimReal+2) * sizeof(kiss_fft_scalar)  // freq buffer for one pass
        + dimOther*(dimReal+2) * sizeof(kiss_fft_scalar);  // large enough to hold entire input in case of in-place

    memneeded = sizeof( struct kiss_fftndr_state ) + nr + nd + ntmp;

    if (lenmem==NULL) {
        st = (kiss_fftndr_cfg) malloc(memneeded);
    }else{
        if (*lenmem >= memneeded)
            st = (kiss_fftndr_cfg)mem;
        *lenmem = memneeded; 
    }
    if (st==NULL)
        return NULL;
    memset( st , 0 , memneeded);
    
    st->dimReal = dimReal;
    st->dimOther = dimOther;
    st->cfg_r = kiss_fftr_alloc( dimReal,inverse_fft,st+1,&nr);
    st->cfg_nd = kiss_fftnd_alloc(dims,ndims-1,inverse_fft, ((char*) st->cfg_r)+nr,&nd);
    st->tmpbuf = (char*)st->cfg_nd + nd;

    return st;
}