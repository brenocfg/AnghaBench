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
struct TYPE_6__ {unsigned int bitdepth; int /*<<< orphan*/  colortype; } ;
struct TYPE_7__ {TYPE_1__ info_raw; } ;
typedef  TYPE_2__ LodePNGState ;
typedef  int /*<<< orphan*/  LodePNGColorType ;

/* Variables and functions */
 unsigned int lodepng_decode (unsigned char**,unsigned int*,unsigned int*,TYPE_2__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  lodepng_state_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  lodepng_state_init (TYPE_2__*) ; 

unsigned lodepng_decode_memory(unsigned char** out, unsigned* w, unsigned* h, const unsigned char* in,
                               size_t insize, LodePNGColorType colortype, unsigned bitdepth)
{
  unsigned error;
  LodePNGState state;
  lodepng_state_init(&state);
  state.info_raw.colortype = colortype;
  state.info_raw.bitdepth = bitdepth;
  error = lodepng_decode(out, w, h, &state, in, insize);
  lodepng_state_cleanup(&state);
  return error;
}