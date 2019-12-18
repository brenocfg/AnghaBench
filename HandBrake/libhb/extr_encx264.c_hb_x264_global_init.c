#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_bitdepth; } ;
typedef  TYPE_1__ x264_param_t ;
struct TYPE_5__ {int bit_depth; int /*<<< orphan*/ * picture_init; int /*<<< orphan*/ * encoder_close; int /*<<< orphan*/ * encoder_delayed_frames; int /*<<< orphan*/ * encoder_encode; int /*<<< orphan*/ * encoder_headers; int /*<<< orphan*/ * encoder_open; int /*<<< orphan*/ * param_parse; int /*<<< orphan*/ * param_apply_fastfirstpass; int /*<<< orphan*/ * param_apply_profile; int /*<<< orphan*/ * param_default_preset; int /*<<< orphan*/  (* param_default ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int X264_BIT_DEPTH ; 
 int /*<<< orphan*/  free (char*) ; 
 void* hb_dlsym (void*,char*) ; 
 char* hb_strdup_printf (char*,int) ; 
 int /*<<< orphan*/  libx264_10bit_names ; 
 int /*<<< orphan*/  libx264_8bit_names ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_2__* x264_apis ; 
 int x264_bit_depth ; 
 void* x264_encoder_close ; 
 void* x264_encoder_delayed_frames ; 
 void* x264_encoder_encode ; 
 void* x264_encoder_headers ; 
 void* x264_encoder_open ; 
 void* x264_lib_open (int /*<<< orphan*/ ) ; 
 void* x264_lib_open_ubuntu_10bit () ; 
 void* x264_param_apply_fastfirstpass ; 
 void* x264_param_apply_profile ; 
 void* x264_param_default ; 
 void* x264_param_default_preset ; 
 void* x264_param_parse ; 
 void* x264_picture_init ; 

void hb_x264_global_init(void)
{
#if X264_BUILD < 153
    x264_apis[0].bit_depth                 = x264_bit_depth;
#else
    x264_apis[0].bit_depth                 = X264_BIT_DEPTH;
#endif
    x264_apis[0].param_default             = x264_param_default;
    x264_apis[0].param_default_preset      = x264_param_default_preset;
    x264_apis[0].param_apply_profile       = x264_param_apply_profile;
    x264_apis[0].param_apply_fastfirstpass = x264_param_apply_fastfirstpass;
    x264_apis[0].param_parse               = x264_param_parse;
    x264_apis[0].encoder_open              = x264_encoder_open;
    x264_apis[0].encoder_headers           = x264_encoder_headers;
    x264_apis[0].encoder_encode            = x264_encoder_encode;
    x264_apis[0].encoder_delayed_frames    = x264_encoder_delayed_frames;
    x264_apis[0].encoder_close             = x264_encoder_close;
    x264_apis[0].picture_init              = x264_picture_init;

    if (x264_apis[0].bit_depth == 0)
    {
        // libx264 supports 8 and 10 bit
        x264_apis[0].bit_depth                 = 8;
        x264_apis[1].bit_depth                 = 10;
        x264_apis[1].param_default             = x264_param_default;
        x264_apis[1].param_default_preset      = x264_param_default_preset;
        x264_apis[1].param_apply_profile       = x264_param_apply_profile;
        x264_apis[1].param_apply_fastfirstpass = x264_param_apply_fastfirstpass;
        x264_apis[1].param_parse               = x264_param_parse;
        x264_apis[1].encoder_open              = x264_encoder_open;
        x264_apis[1].encoder_headers           = x264_encoder_headers;
        x264_apis[1].encoder_encode            = x264_encoder_encode;
        x264_apis[1].encoder_delayed_frames    = x264_encoder_delayed_frames;
        x264_apis[1].encoder_close             = x264_encoder_close;
        x264_apis[1].picture_init              = x264_picture_init;
        return;
    }

    // Invalidate other apis
    x264_apis[1].bit_depth = -1;

    // Attempt to dlopen a library for handling the bit-depth that we do
    // not already have.
    void *h;
    if (x264_apis[0].bit_depth == 8)
    {
        h = x264_lib_open(libx264_10bit_names);
#if defined(SYS_LINUX)
        if (h == NULL)
        {
            h = x264_lib_open_ubuntu_10bit();
        }
#endif
    }
    else
    {
        h = x264_lib_open(libx264_8bit_names);
    }
    if (h == NULL)
    {
        return;
    }

    int ii;
    int dll_bitdepth = 0;
#if X264_BUILD < 153
    int *pbit_depth                   = (int*)hb_dlsym(h, "x264_bit_depth");
    if (pbit_depth != NULL)
    {
        dll_bitdepth = *pbit_depth;
    }
#endif
    x264_apis[1].param_default        = hb_dlsym(h, "x264_param_default");
#if X264_BUILD >= 153
    if (x264_apis[1].param_default != NULL)
    {
        x264_param_t defaults;
        x264_apis[1].param_default(&defaults);
        dll_bitdepth = defaults.i_bitdepth;
    }
#endif
    x264_apis[1].param_default_preset = hb_dlsym(h, "x264_param_default_preset");
    x264_apis[1].param_apply_profile  = hb_dlsym(h, "x264_param_apply_profile");
    x264_apis[1].param_apply_fastfirstpass =
                                hb_dlsym(h, "x264_param_apply_fastfirstpass");
    x264_apis[1].param_parse          = hb_dlsym(h, "x264_param_parse");
    // x264 appends the build number to the end of x264_encoder_open
    for (ii = 140; ii < 200; ii++)
    {
        char *name = hb_strdup_printf("x264_encoder_open_%d", ii);
        x264_apis[1].encoder_open = hb_dlsym(h, name);
        free(name);
        if (x264_apis[1].encoder_open != NULL)
        {
            break;
        }
    }
    x264_apis[1].encoder_headers      = hb_dlsym(h, "x264_encoder_headers");
    x264_apis[1].encoder_encode       = hb_dlsym(h, "x264_encoder_encode");
    x264_apis[1].encoder_delayed_frames =
                                hb_dlsym(h, "x264_encoder_delayed_frames");
    x264_apis[1].encoder_close        = hb_dlsym(h, "x264_encoder_close");
    x264_apis[1].picture_init         = hb_dlsym(h, "x264_picture_init");

    if (dll_bitdepth > 0 && dll_bitdepth != x264_apis[0].bit_depth &&
        x264_apis[1].param_default             != NULL &&
        x264_apis[1].param_default_preset      != NULL &&
        x264_apis[1].param_apply_profile       != NULL &&
        x264_apis[1].param_apply_fastfirstpass != NULL &&
        x264_apis[1].param_parse               != NULL &&
        x264_apis[1].encoder_open              != NULL &&
        x264_apis[1].encoder_headers           != NULL &&
        x264_apis[1].encoder_encode            != NULL &&
        x264_apis[1].encoder_delayed_frames    != NULL &&
        x264_apis[1].encoder_close             != NULL &&
        x264_apis[1].picture_init              != NULL)
    {
        x264_apis[1].bit_depth = dll_bitdepth;
    }
}