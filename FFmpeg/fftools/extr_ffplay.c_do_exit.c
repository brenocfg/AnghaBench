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
typedef  int /*<<< orphan*/  VideoState ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_QUIET ; 
 int /*<<< orphan*/  SDL_DestroyRenderer (scalar_t__) ; 
 int /*<<< orphan*/  SDL_DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  avformat_network_deinit () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ renderer ; 
 scalar_t__ show_status ; 
 int /*<<< orphan*/  stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uninit_opts () ; 
 int /*<<< orphan*/  vfilters_list ; 
 scalar_t__ window ; 

__attribute__((used)) static void do_exit(VideoState *is)
{
    if (is) {
        stream_close(is);
    }
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    uninit_opts();
#if CONFIG_AVFILTER
    av_freep(&vfilters_list);
#endif
    avformat_network_deinit();
    if (show_status)
        printf("\n");
    SDL_Quit();
    av_log(NULL, AV_LOG_QUIET, "%s", "");
    exit(0);
}