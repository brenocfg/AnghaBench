#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hb_filter_private_s {int dummy; } ;
struct TYPE_5__ {void* output; int /*<<< orphan*/ * avfilters; void* input; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_6__ {int /*<<< orphan*/ * settings; TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
typedef  void* hb_filter_init_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hb_dict_extract_int (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_extract_string (char**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_dict_set_double (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  hb_dict_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hb_dict_set_string (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int deblock_init(hb_filter_object_t * filter, hb_filter_init_t * init)
{
    hb_filter_private_t * pv = NULL;

    pv = calloc(1, sizeof(struct hb_filter_private_s));
    filter->private_data = pv;
    if (pv == NULL)
    {
        return 1;
    }
    pv->input = *init;

    hb_dict_t        * settings = filter->settings;

    int      thresh   = -1, blocksize = 8;
    char  *  strength = NULL;

    hb_dict_extract_string(&strength, settings, "strength");
    hb_dict_extract_int(&thresh, settings, "thresh");
    hb_dict_extract_int(&blocksize, settings, "blocksize");

    hb_dict_t * avfilter = hb_dict_init();
    hb_dict_t * avsettings = hb_dict_init();

    if (strength != NULL)
    {
        hb_dict_set_string(avsettings, "filter", strength);
        free(strength);
    }
    hb_dict_set_int(avsettings, "block", blocksize);

    if (thresh > 0)
    {
        double alpha, beta, gamma, delta;

        alpha = thresh * 0.010;
        beta  = gamma = delta = alpha / 2;
        hb_dict_set_double(avsettings, "alpha", alpha);
        hb_dict_set_double(avsettings, "beta", beta);
        hb_dict_set_double(avsettings, "gamma", gamma);
        hb_dict_set_double(avsettings, "delta", delta);
    }
    hb_dict_set(avfilter, "deblock", avsettings);
    pv->avfilters = avfilter;

    pv->output = *init;

    return 0;
}