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
 int /*<<< orphan*/  disable_hardware ; 
 int /*<<< orphan*/  hb_avcodec_init () ; 
 int /*<<< orphan*/  hb_buffer_pool_init () ; 
 int /*<<< orphan*/  hb_common_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_decavcodeca ; 
 int /*<<< orphan*/  hb_decavcodecv ; 
 int /*<<< orphan*/  hb_deccc608 ; 
 int /*<<< orphan*/  hb_declpcm ; 
 int /*<<< orphan*/  hb_decpgssub ; 
 int /*<<< orphan*/  hb_decsrtsub ; 
 int /*<<< orphan*/  hb_decssasub ; 
 int /*<<< orphan*/  hb_dectx3gsub ; 
 int /*<<< orphan*/  hb_decutf8sub ; 
 int /*<<< orphan*/  hb_decvobsub ; 
 int /*<<< orphan*/  hb_encavcodec ; 
 int /*<<< orphan*/  hb_encavcodeca ; 
 int /*<<< orphan*/  hb_encca_aac ; 
 int /*<<< orphan*/  hb_encca_haac ; 
 int /*<<< orphan*/  hb_encqsv ; 
 int /*<<< orphan*/  hb_enctheora ; 
 int /*<<< orphan*/  hb_encvobsub ; 
 int /*<<< orphan*/  hb_encvorbis ; 
 int /*<<< orphan*/  hb_encx264 ; 
 int /*<<< orphan*/  hb_encx265 ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  hb_muxer ; 
 int /*<<< orphan*/  hb_param_configure_qsv () ; 
 int hb_platform_init () ; 
 int /*<<< orphan*/  hb_presets_builtin_init () ; 
 int hb_qsv_info_init () ; 
 int /*<<< orphan*/  hb_reader ; 
 int /*<<< orphan*/  hb_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_sync_audio ; 
 int /*<<< orphan*/  hb_sync_subtitle ; 
 int /*<<< orphan*/  hb_sync_video ; 
 int /*<<< orphan*/  hb_x264_global_init () ; 

int hb_global_init()
{
    /* Print hardening status on global init */
#if HB_PROJECT_SECURITY_HARDEN
    hb_log( "Compile-time hardening features are enabled" );
#endif

    int result = 0;

    result = hb_platform_init();
    if (result < 0)
    {
        hb_error("Platform specific initialization failed!");
        return -1;
    }

#if HB_PROJECT_FEATURE_QSV
    if (!disable_hardware)
    {
        result = hb_qsv_info_init();
        if (result < 0)
        {
            hb_error("hb_qsv_info_init failed!");
            return -1;
        }
        hb_param_configure_qsv();
    }
#endif

    /* libavcodec */
    hb_avcodec_init();

    /* HB work objects */
    hb_register(&hb_muxer);
    hb_register(&hb_reader);
    hb_register(&hb_sync_video);
    hb_register(&hb_sync_audio);
    hb_register(&hb_sync_subtitle);
    hb_register(&hb_decavcodecv);
    hb_register(&hb_decavcodeca);
    hb_register(&hb_declpcm);
    hb_register(&hb_deccc608);
    hb_register(&hb_decpgssub);
    hb_register(&hb_decsrtsub);
    hb_register(&hb_decssasub);
    hb_register(&hb_dectx3gsub);
    hb_register(&hb_decutf8sub);
    hb_register(&hb_decvobsub);
    hb_register(&hb_encvobsub);
    hb_register(&hb_encavcodec);
    hb_register(&hb_encavcodeca);
#ifdef __APPLE__
    hb_register(&hb_encca_aac);
    hb_register(&hb_encca_haac);
#endif
    hb_register(&hb_enctheora);
    hb_register(&hb_encvorbis);
    hb_register(&hb_encx264);
#if HB_PROJECT_FEATURE_X265
    hb_register(&hb_encx265);
#endif
#if HB_PROJECT_FEATURE_QSV
    if (!disable_hardware)
    {
        hb_register(&hb_encqsv);
    }
#endif

    hb_x264_global_init();
    hb_common_global_init(disable_hardware);

    /*
     * Initialise buffer pool
     */
    hb_buffer_pool_init();

    // Initialize the builtin presets hb_dict_t
    hb_presets_builtin_init();

    return result;
}