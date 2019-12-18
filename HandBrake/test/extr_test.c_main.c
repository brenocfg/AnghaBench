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
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 scalar_t__ CheckOptions (int,char**) ; 
 int /*<<< orphan*/  EventLoop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int HB_ERROR_WRONG_INPUT ; 
 char* HB_PROJECT_HOST_TITLE ; 
 char* HB_PROJECT_TITLE ; 
 char* HB_PROJECT_URL_WEBSITE ; 
 scalar_t__ ParseOptions (int,char**) ; 
 int /*<<< orphan*/ * PreparePreset (char*) ; 
 int /*<<< orphan*/  RunQueue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SigHandler ; 
 int /*<<< orphan*/  abitrates ; 
 char* acodec_fallback ; 
 int /*<<< orphan*/  acodecs ; 
 int /*<<< orphan*/  acompressions ; 
 char* advanced_opts ; 
 int /*<<< orphan*/  aqualities ; 
 int /*<<< orphan*/  arates ; 
 int /*<<< orphan*/  atracks ; 
 int /*<<< orphan*/  audio_copy_list ; 
 int /*<<< orphan*/  audio_dither ; 
 int /*<<< orphan*/  audio_gain ; 
 int /*<<< orphan*/  audio_lang_list ; 
 char* chroma_smooth ; 
 char* chroma_smooth_tune ; 
 char* deblock ; 
 char* deblock_tune ; 
 int /*<<< orphan*/  debug ; 
 char* decomb ; 
 char* deinterlace ; 
 char* detelecine ; 
 int done_error ; 
 int /*<<< orphan*/  dvdnav ; 
 int /*<<< orphan*/  dynamic_range_compression ; 
 char* encoder_level ; 
 char* encoder_preset ; 
 char* encoder_profile ; 
 char* encoder_tune ; 
 char* format ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_argv_utf8 (int*,char***) ; 
 int /*<<< orphan*/  hb_cli_error_handler ; 
 int /*<<< orphan*/  hb_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_dvd_set_dvdnav (int /*<<< orphan*/ ) ; 
 int hb_get_cpu_count () ; 
 int /*<<< orphan*/  hb_global_close () ; 
 int /*<<< orphan*/  hb_global_init () ; 
 int /*<<< orphan*/ * hb_init (int) ; 
 int /*<<< orphan*/  hb_log_level_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_presets_builtin_update () ; 
 int /*<<< orphan*/  hb_presets_cli_default_init () ; 
 char* hb_presets_package_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_presets_write_json (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_register_error_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_scan (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  hb_str_vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_system_sleep_prevent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_value_string (char*) ; 
 char* hqdn3d ; 
 char* input ; 
 char* lapsharp ; 
 char* lapsharp_tune ; 
 scalar_t__ main_feature ; 
 long long min_title_duration ; 
 int /*<<< orphan*/  mixdowns ; 
 char* native_language ; 
 char* nlmeans ; 
 char* nlmeans_tune ; 
 char* output ; 
 char* preset_export_desc ; 
 char* preset_export_file ; 
 char* preset_export_name ; 
 char* preset_name ; 
 int /*<<< orphan*/  preview_count ; 
 int /*<<< orphan*/ * queue_import_name ; 
 char* rotate ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  store_previews ; 
 int /*<<< orphan*/  subtitle_lang_list ; 
 int /*<<< orphan*/  subtracks ; 
 int /*<<< orphan*/  test_tty () ; 
 scalar_t__ titleindex ; 
 int /*<<< orphan*/  titlescan ; 
 char* unsharp ; 
 char* unsharp_tune ; 

int main( int argc, char ** argv )
{
    hb_handle_t * h;

    hb_global_init();
    hb_presets_builtin_update();
    hb_presets_cli_default_init();

    /* Init libhb */
    h = hb_init(4);  // Show all logging until debug level is parsed

    test_tty(); // Terminal detection

    // Get utf8 command line if windows
    get_argv_utf8(&argc, &argv);

    /* Parse command line */
    if( ParseOptions( argc, argv ) ||
        CheckOptions( argc, argv ) )
    {
        hb_log_level_set(h, debug);
        goto cleanup;
    }

    hb_log_level_set(h, debug);

    /* Register our error handler */
    hb_register_error_handler(&hb_cli_error_handler);

    hb_dvd_set_dvdnav( dvdnav );

    /* Show version */
    fprintf( stderr, "%s - %s - %s\n",
             HB_PROJECT_TITLE, HB_PROJECT_HOST_TITLE, HB_PROJECT_URL_WEBSITE );

    /* Geeky */
    fprintf( stderr, "%d CPU%s detected\n", hb_get_cpu_count(),
             hb_get_cpu_count() > 1 ? "s" : "" );

    /* Exit ASAP on Ctrl-C */
    signal( SIGINT, SigHandler );

    if (queue_import_name != NULL)
    {
        hb_system_sleep_prevent(h);
        RunQueue(h, queue_import_name);
    }
    else
    {
        // Apply all command line overrides to the preset that are possible.
        // Some command line options are applied later to the job
        // (e.g. chapter names, explicit audio & subtitle tracks).
        hb_dict_t *preset_dict = PreparePreset(preset_name);
        if (preset_dict == NULL)
        {
            // An appropriate error message should have already
            // been spilled by PreparePreset.
            done_error = HB_ERROR_WRONG_INPUT;
            goto cleanup;
        }

        if (preset_export_name != NULL)
        {
            hb_dict_set(preset_dict, "PresetName",
                        hb_value_string(preset_export_name));
            if (preset_export_desc != NULL)
            {
                hb_dict_set(preset_dict, "PresetDescription",
                            hb_value_string(preset_export_desc));
            }
            if (preset_export_file != NULL)
            {
                hb_presets_write_json(preset_dict, preset_export_file);
            }
            else
            {
                char *json;
                json = hb_presets_package_json(preset_dict);
                fprintf(stdout, "%s\n", json);
            }
            // If the user requested to export a preset, but not to
            // transcode or scan a file, exit here.
            if (input == NULL ||
                (!titlescan && titleindex != 0 && output == NULL))
            {
                hb_value_free(&preset_dict);
                goto cleanup;
            }
        }

        /* Feed libhb with a DVD to scan */
        fprintf( stderr, "Opening %s...\n", input );

        if (main_feature) {
            /*
             * We need to scan for all the titles in order to
             * find the main feature
             */
            titleindex = 0;
        }

        hb_system_sleep_prevent(h);

        hb_scan(h, input, titleindex, preview_count, store_previews,
                min_title_duration * 90000LL);

        EventLoop(h, preset_dict);
        hb_value_free(&preset_dict);
    }

cleanup:
    /* Clean up */
    hb_close(&h);
    hb_global_close();
    hb_str_vfree(audio_copy_list);
    hb_str_vfree(abitrates);
    hb_str_vfree(acompressions);
    hb_str_vfree(aqualities);
    hb_str_vfree(audio_dither);
    hb_str_vfree(acodecs);
    hb_str_vfree(arates);
    hb_str_vfree(atracks);
    hb_str_vfree(audio_lang_list);
    hb_str_vfree(audio_gain);
    hb_str_vfree(dynamic_range_compression);
    hb_str_vfree(mixdowns);
    hb_str_vfree(subtitle_lang_list);
    hb_str_vfree(subtracks);
    free(acodec_fallback);
    free(native_language);
    free(format);
    free(input);
    free(output);
    free(preset_name);
    free(encoder_preset);
    free(encoder_tune);
    free(advanced_opts);
    free(encoder_profile);
    free(encoder_level);
    free(rotate);
    free(deblock);
    free(deblock_tune);
    free(detelecine);
    free(deinterlace);
    free(decomb);
    free(hqdn3d);
    free(nlmeans);
    free(nlmeans_tune);
    free(chroma_smooth);
    free(chroma_smooth_tune);
    free(unsharp);
    free(unsharp_tune);
    free(lapsharp);
    free(lapsharp_tune);
    free(preset_export_name);
    free(preset_export_desc);
    free(preset_export_file);

    // write a carriage return to stdout
    // avoids overlap / line wrapping when stderr is redirected
    fprintf(stdout, "\n");
    fprintf(stderr, "HandBrake has exited.\n");

    return done_error;
}