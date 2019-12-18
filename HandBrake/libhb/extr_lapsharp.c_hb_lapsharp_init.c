#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hb_filter_private_s {int dummy; } ;
struct TYPE_6__ {int strength; int kernel; } ;
typedef  TYPE_1__ lapsharp_plane_context_t ;
struct TYPE_7__ {void* output; TYPE_1__* plane_ctx; void* input; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_8__ {int /*<<< orphan*/ * settings; TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_filter_object_t ;
typedef  void* hb_filter_init_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int LAPSHARP_KERNELS ; 
 void* LAPSHARP_KERNEL_CHROMA_DEFAULT ; 
 void* LAPSHARP_KERNEL_LUMA_DEFAULT ; 
 int LAPSHARP_STRENGTH_CHROMA_DEFAULT ; 
 int LAPSHARP_STRENGTH_LUMA_DEFAULT ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hb_dict_extract_double (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_extract_string (char**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static int hb_lapsharp_init(hb_filter_object_t *filter,
                            hb_filter_init_t   *init)
{
    filter->private_data = calloc(sizeof(struct hb_filter_private_s), 1);
    hb_filter_private_t * pv = filter->private_data;

    char *kernel_string[3];

    pv->input = *init;

    // Mark parameters unset
    for (int c = 0; c < 3; c++)
    {
        pv->plane_ctx[c].strength = -1;
        pv->plane_ctx[c].kernel   = -1;
        kernel_string[c]          = NULL;
    }

    // Read user parameters
    if (filter->settings != NULL)
    {
        hb_dict_t * dict = filter->settings;
        hb_dict_extract_double(&pv->plane_ctx[0].strength, dict, "y-strength");
        hb_dict_extract_string(&kernel_string[0],          dict, "y-kernel");

        hb_dict_extract_double(&pv->plane_ctx[1].strength, dict, "cb-strength");
        hb_dict_extract_string(&kernel_string[1],          dict, "cb-kernel");

        hb_dict_extract_double(&pv->plane_ctx[2].strength, dict, "cr-strength");
        hb_dict_extract_string(&kernel_string[2],          dict, "cr-kernel");
    }

    // Convert kernel user string to internal id
    for (int c = 0; c < 3; c++)
    {
        lapsharp_plane_context_t * ctx = &pv->plane_ctx[c];

        ctx->kernel = -1;

        if (kernel_string[c] == NULL)
        {
            continue;
        }

        if (!strcasecmp(kernel_string[c], "lap"))
        {
            ctx->kernel = 0;
        }
        else if (!strcasecmp(kernel_string[c], "isolap"))
        {
            ctx->kernel = 1;
        }
        else if (!strcasecmp(kernel_string[c], "log"))
        {
            ctx->kernel = 2;
        }
        else if (!strcasecmp(kernel_string[c], "isolog"))
        {
            ctx->kernel = 3;
        }

        free(kernel_string[c]);
    }

    // Cascade values
    // Cr not set; inherit Cb. Cb not set; inherit Y. Y not set; defaults.
    for (int c = 1; c < 3; c++)
    {
        lapsharp_plane_context_t * prev_ctx = &pv->plane_ctx[c - 1];
        lapsharp_plane_context_t * ctx      = &pv->plane_ctx[c];

        if (ctx->strength == -1) ctx->strength = prev_ctx->strength;
        if (ctx->kernel   == -1) ctx->kernel   = prev_ctx->kernel;
    }

    for (int c = 0; c < 3; c++)
    {
        lapsharp_plane_context_t * ctx = &pv->plane_ctx[c];

        // Replace unset values with defaults
        if (ctx->strength == -1)
        {
            ctx->strength = c ? LAPSHARP_STRENGTH_CHROMA_DEFAULT :
                                LAPSHARP_STRENGTH_LUMA_DEFAULT;
        }
        if (ctx->kernel   == -1)
        {
            ctx->kernel   = c ? LAPSHARP_KERNEL_CHROMA_DEFAULT :
                                LAPSHARP_KERNEL_LUMA_DEFAULT;
        }

        // Sanitize
        if (ctx->strength < 0)   ctx->strength = 0;
        if (ctx->strength > 1.5) ctx->strength = 1.5;
        if ((ctx->kernel < 0) || (ctx->kernel >= LAPSHARP_KERNELS))
        {
            ctx->kernel = c ? LAPSHARP_KERNEL_CHROMA_DEFAULT : LAPSHARP_KERNEL_LUMA_DEFAULT;
        }
    }
    pv->output = *init;

    return 0;
}