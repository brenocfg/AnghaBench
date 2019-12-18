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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int HASH_SIZE ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_md5_alloc () ; 
 int /*<<< orphan*/  av_write_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check (int,char*,...) ; 
 scalar_t__ check_faults ; 
 int clear_duration ; 
 int /*<<< orphan*/  close_out () ; 
 int /*<<< orphan*/  ctx ; 
 int do_interleave ; 
 int duration ; 
 int fake_pkt_duration ; 
 int /*<<< orphan*/  finish () ; 
 int force_iobuf_size ; 
 char* format ; 
 int getopt (int,char**,char*) ; 
 int gop_size ; 
 int /*<<< orphan*/  hash ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  init (int,int) ; 
 int /*<<< orphan*/  init_count_warnings () ; 
 int /*<<< orphan*/  init_fps (int,int,int) ; 
 int /*<<< orphan*/  init_out (char*) ; 
 int /*<<< orphan*/  md5 ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mux_frames (int,int) ; 
 int /*<<< orphan*/  mux_gops (int) ; 
 scalar_t__ num_warnings ; 
 int /*<<< orphan*/  opts ; 
 int out_size ; 
 int /*<<< orphan*/  reset_count_warnings () ; 
 int /*<<< orphan*/  signal_init_ts () ; 
 int /*<<< orphan*/  skip_gops (int) ; 
 int skip_write_audio ; 
 int write_file ; 

int main(int argc, char **argv)
{
    int c;
    uint8_t header[HASH_SIZE];
    uint8_t content[HASH_SIZE];
    int empty_moov_pos;
    int prev_pos;

    for (;;) {
        c = getopt(argc, argv, "wh");
        if (c == -1)
            break;
        switch (c) {
        case 'w':
            write_file = 1;
            break;
        default:
        case 'h':
            help();
            return 0;
        }
    }

    md5 = av_md5_alloc();
    if (!md5)
        return 1;

    // Write a fragmented file with an initial moov that actually contains some
    // samples. One moov+mdat with 1 second of data and one moof+mdat with 1
    // second of data.
    init_out("non-empty-moov");
    av_dict_set(&opts, "movflags", "frag_keyframe", 0);
    init(0, 0);
    mux_gops(2);
    finish();
    close_out();

    // Write a similar file, but with B-frames and audio preroll, handled
    // via an edit list.
    init_out("non-empty-moov-elst");
    av_dict_set(&opts, "movflags", "frag_keyframe", 0);
    av_dict_set(&opts, "use_editlist", "1", 0);
    init(1, 1);
    mux_gops(2);
    finish();
    close_out();

    // Use B-frames but no audio-preroll, but without an edit list.
    // Due to avoid_negative_ts == AVFMT_AVOID_NEG_TS_MAKE_ZERO, the dts
    // of the first audio packet is > 0, but it is set to zero since edit
    // lists aren't used, increasing the duration of the first packet instead.
    init_out("non-empty-moov-no-elst");
    av_dict_set(&opts, "movflags", "frag_keyframe", 0);
    av_dict_set(&opts, "use_editlist", "0", 0);
    init(1, 0);
    mux_gops(2);
    finish();
    close_out();

    format = "ismv";
    // Write an ISMV, with B-frames and audio preroll.
    init_out("ismv");
    av_dict_set(&opts, "movflags", "frag_keyframe", 0);
    init(1, 1);
    mux_gops(2);
    finish();
    close_out();
    format = "mp4";

    // An initial moov that doesn't contain any samples, followed by two
    // moof+mdat pairs.
    init_out("empty-moov");
    av_dict_set(&opts, "movflags", "frag_keyframe+empty_moov", 0);
    av_dict_set(&opts, "use_editlist", "0", 0);
    init(0, 0);
    mux_gops(2);
    finish();
    close_out();
    memcpy(content, hash, HASH_SIZE);

    // Similar to the previous one, but with input that doesn't start at
    // pts/dts 0. avoid_negative_ts behaves in the same way as
    // in non-empty-moov-no-elst above.
    init_out("empty-moov-no-elst");
    av_dict_set(&opts, "movflags", "frag_keyframe+empty_moov", 0);
    init(1, 0);
    mux_gops(2);
    finish();
    close_out();

    // Same as the previous one, but disable avoid_negative_ts (which
    // would require using an edit list, but with empty_moov, one can't
    // write a sensible edit list, when the start timestamps aren't known).
    // This should trigger a warning - we check that the warning is produced.
    init_count_warnings();
    init_out("empty-moov-no-elst-no-adjust");
    av_dict_set(&opts, "movflags", "frag_keyframe+empty_moov", 0);
    av_dict_set(&opts, "avoid_negative_ts", "0", 0);
    init(1, 0);
    mux_gops(2);
    finish();
    close_out();

    reset_count_warnings();
    check(num_warnings > 0, "No warnings printed for unhandled start offset");

    // Verify that delay_moov produces the same as empty_moov for
    // simple input
    init_out("delay-moov");
    av_dict_set(&opts, "movflags", "frag_keyframe+delay_moov", 0);
    av_dict_set(&opts, "use_editlist", "0", 0);
    init(0, 0);
    mux_gops(2);
    finish();
    close_out();
    check(!memcmp(hash, content, HASH_SIZE), "delay_moov differs from empty_moov");

    // Test writing content that requires an edit list using delay_moov
    init_out("delay-moov-elst");
    av_dict_set(&opts, "movflags", "frag_keyframe+delay_moov", 0);
    init(1, 1);
    mux_gops(2);
    finish();
    close_out();

    // Test writing a file with one track lacking packets, with delay_moov.
    skip_write_audio = 1;
    init_out("delay-moov-empty-track");
    av_dict_set(&opts, "movflags", "frag_keyframe+delay_moov", 0);
    init(0, 0);
    mux_gops(2);
    // The automatic flushing shouldn't output anything, since we're still
    // waiting for data for some tracks
    check(out_size == 0, "delay_moov flushed prematurely");
    // When closed (or manually flushed), all the written data should still
    // be output.
    finish();
    close_out();
    check(out_size > 0, "delay_moov didn't output anything");

    // Check that manually flushing still outputs things as expected. This
    // produces two fragments, while the one above produces only one.
    init_out("delay-moov-empty-track-flush");
    av_dict_set(&opts, "movflags", "frag_custom+delay_moov", 0);
    init(0, 0);
    mux_gops(1);
    av_write_frame(ctx, NULL); // Force writing the moov
    check(out_size > 0, "No moov written");
    av_write_frame(ctx, NULL);
    mux_gops(1);
    av_write_frame(ctx, NULL);
    finish();
    close_out();

    skip_write_audio = 0;



    // Verify that the header written by delay_moov when manually flushed
    // is identical to the one by empty_moov.
    init_out("empty-moov-header");
    av_dict_set(&opts, "movflags", "frag_keyframe+empty_moov", 0);
    av_dict_set(&opts, "use_editlist", "0", 0);
    init(0, 0);
    close_out();
    memcpy(header, hash, HASH_SIZE);
    init_out("empty-moov-content");
    mux_gops(2);
    // Written 2 seconds of content, with an automatic flush after 1 second.
    check(out_size > 0, "No automatic flush?");
    empty_moov_pos = prev_pos = out_size;
    // Manually flush the second fragment
    av_write_frame(ctx, NULL);
    check(out_size > prev_pos, "No second fragment flushed?");
    prev_pos = out_size;
    // Check that an extra flush doesn't output any more data
    av_write_frame(ctx, NULL);
    check(out_size == prev_pos, "More data written?");
    close_out();
    memcpy(content, hash, HASH_SIZE);
    // Ignore the trailer written here
    finish();

    init_out("delay-moov-header");
    av_dict_set(&opts, "movflags", "frag_custom+delay_moov", 0);
    av_dict_set(&opts, "use_editlist", "0", 0);
    init(0, 0);
    check(out_size == 0, "Output written during init with delay_moov");
    mux_gops(1); // Write 1 second of content
    av_write_frame(ctx, NULL); // Force writing the moov
    close_out();
    check(!memcmp(hash, header, HASH_SIZE), "delay_moov header differs from empty_moov");
    init_out("delay-moov-content");
    av_write_frame(ctx, NULL); // Flush the first fragment
    check(out_size == empty_moov_pos, "Manually flushed content differs from automatically flushed, %d vs %d", out_size, empty_moov_pos);
    mux_gops(1); // Write the rest of the content
    av_write_frame(ctx, NULL); // Flush the second fragment
    close_out();
    check(!memcmp(hash, content, HASH_SIZE), "delay_moov content differs from empty_moov");
    finish();


    // Verify that we can produce an identical second fragment without
    // writing the first one. First write the reference fragments that
    // we want to reproduce.
    av_dict_set(&opts, "movflags", "frag_custom+empty_moov+dash", 0);
    init(0, 0);
    mux_gops(1);
    av_write_frame(ctx, NULL); // Output the first fragment
    init_out("empty-moov-second-frag");
    mux_gops(1);
    av_write_frame(ctx, NULL); // Output the second fragment
    close_out();
    memcpy(content, hash, HASH_SIZE);
    finish();

    // Produce the same second fragment without actually writing the first
    // one before.
    av_dict_set(&opts, "movflags", "frag_custom+empty_moov+dash+frag_discont", 0);
    av_dict_set(&opts, "fragment_index", "2", 0);
    av_dict_set(&opts, "avoid_negative_ts", "0", 0);
    av_dict_set(&opts, "use_editlist", "0", 0);
    init(0, 0);
    skip_gops(1);
    init_out("empty-moov-second-frag-discont");
    mux_gops(1);
    av_write_frame(ctx, NULL); // Output the second fragment
    close_out();
    check(!memcmp(hash, content, HASH_SIZE), "discontinuously written fragment differs");
    finish();

    // Produce the same thing by using delay_moov, which requires a slightly
    // different call sequence.
    av_dict_set(&opts, "movflags", "frag_custom+delay_moov+dash+frag_discont", 0);
    av_dict_set(&opts, "fragment_index", "2", 0);
    init(0, 0);
    skip_gops(1);
    mux_gops(1);
    av_write_frame(ctx, NULL); // Output the moov
    init_out("delay-moov-second-frag-discont");
    av_write_frame(ctx, NULL); // Output the second fragment
    close_out();
    check(!memcmp(hash, content, HASH_SIZE), "discontinuously written fragment differs");
    finish();


    // Test discontinuously written fragments with B-frames (where the
    // assumption of starting at pts=0 works) but not with audio preroll
    // (which can't be guessed).
    av_dict_set(&opts, "movflags", "frag_custom+delay_moov+dash", 0);
    init(1, 0);
    mux_gops(1);
    init_out("delay-moov-elst-init");
    av_write_frame(ctx, NULL); // Output the moov
    close_out();
    memcpy(header, hash, HASH_SIZE);
    av_write_frame(ctx, NULL); // Output the first fragment
    init_out("delay-moov-elst-second-frag");
    mux_gops(1);
    av_write_frame(ctx, NULL); // Output the second fragment
    close_out();
    memcpy(content, hash, HASH_SIZE);
    finish();

    av_dict_set(&opts, "movflags", "frag_custom+delay_moov+dash+frag_discont", 0);
    av_dict_set(&opts, "fragment_index", "2", 0);
    init(1, 0);
    skip_gops(1);
    mux_gops(1); // Write the second fragment
    init_out("delay-moov-elst-init-discont");
    av_write_frame(ctx, NULL); // Output the moov
    close_out();
    check(!memcmp(hash, header, HASH_SIZE), "discontinuously written header differs");
    init_out("delay-moov-elst-second-frag-discont");
    av_write_frame(ctx, NULL); // Output the second fragment
    close_out();
    check(!memcmp(hash, content, HASH_SIZE), "discontinuously written fragment differs");
    finish();


    // Test discontinuously written fragments with B-frames and audio preroll,
    // properly signaled.
    av_dict_set(&opts, "movflags", "frag_custom+delay_moov+dash", 0);
    init(1, 1);
    mux_gops(1);
    init_out("delay-moov-elst-signal-init");
    av_write_frame(ctx, NULL); // Output the moov
    close_out();
    memcpy(header, hash, HASH_SIZE);
    av_write_frame(ctx, NULL); // Output the first fragment
    init_out("delay-moov-elst-signal-second-frag");
    mux_gops(1);
    av_write_frame(ctx, NULL); // Output the second fragment
    close_out();
    memcpy(content, hash, HASH_SIZE);
    finish();

    av_dict_set(&opts, "movflags", "frag_custom+delay_moov+dash+frag_discont", 0);
    av_dict_set(&opts, "fragment_index", "2", 0);
    init(1, 1);
    signal_init_ts();
    skip_gops(1);
    mux_gops(1); // Write the second fragment
    init_out("delay-moov-elst-signal-init-discont");
    av_write_frame(ctx, NULL); // Output the moov
    close_out();
    check(!memcmp(hash, header, HASH_SIZE), "discontinuously written header differs");
    init_out("delay-moov-elst-signal-second-frag-discont");
    av_write_frame(ctx, NULL); // Output the second fragment
    close_out();
    check(!memcmp(hash, content, HASH_SIZE), "discontinuously written fragment differs");
    finish();


    // Test muxing discontinuous fragments with very large (> (1<<31)) timestamps.
    av_dict_set(&opts, "movflags", "frag_custom+delay_moov+dash+frag_discont", 0);
    av_dict_set(&opts, "fragment_index", "2", 0);
    init(1, 1);
    signal_init_ts();
    skip_gops(1);
    mux_frames(gop_size, 1); // Write the second fragment
    init_out("delay-moov-elst-signal-init-discont-largets");
    av_write_frame(ctx, NULL); // Output the moov
    close_out();
    init_out("delay-moov-elst-signal-second-frag-discont-largets");
    av_write_frame(ctx, NULL); // Output the second fragment
    close_out();
    finish();

    // Test VFR content, with sidx atoms (which declare the pts duration
    // of a fragment, forcing overriding the start pts of the next one).
    // Here, the fragment duration in pts is significantly different from
    // the duration in dts. The video stream starts at dts=-10,pts=0, and
    // the second fragment starts at dts=155,pts=156. The trun duration sum
    // of the first fragment is 165, which also is written as
    // baseMediaDecodeTime in the tfdt in the second fragment. The sidx for
    // the first fragment says earliest_presentation_time = 0 and
    // subsegment_duration = 156, which also matches the sidx in the second
    // fragment. For the audio stream, the pts and dts durations also don't
    // match - the input stream starts at pts=-2048, but that part is excluded
    // by the edit list.
    init_out("vfr");
    av_dict_set(&opts, "movflags", "frag_keyframe+delay_moov+dash", 0);
    init_fps(1, 1, 3);
    mux_frames(gop_size/2, 0);
    duration /= 10;
    mux_frames(gop_size/2, 0);
    mux_gops(1);
    finish();
    close_out();

    // Test VFR content, with cleared duration fields. In these cases,
    // the muxer must guess the duration of the last packet of each
    // fragment. As long as the framerate doesn't vary (too much) at the
    // fragment edge, it works just fine. Additionally, when automatically
    // cutting fragments, the muxer already know the timestamps of the next
    // packet for one stream (in most cases the video stream), avoiding
    // having to use guesses for that one.
    init_count_warnings();
    clear_duration = 1;
    init_out("vfr-noduration");
    av_dict_set(&opts, "movflags", "frag_keyframe+delay_moov+dash", 0);
    init_fps(1, 1, 3);
    mux_frames(gop_size/2, 0);
    duration /= 10;
    mux_frames(gop_size/2, 0);
    mux_gops(1);
    finish();
    close_out();
    clear_duration = 0;
    reset_count_warnings();
    check(num_warnings > 0, "No warnings printed for filled in durations");

    // Test with an IO buffer size that is too small to hold a full fragment;
    // this will cause write_data_type to be called with the type unknown.
    force_iobuf_size = 1500;
    init_out("large_frag");
    av_dict_set(&opts, "movflags", "frag_keyframe+delay_moov", 0);
    init_fps(1, 1, 3);
    mux_gops(2);
    finish();
    close_out();
    force_iobuf_size = 0;

    // Test VFR content with bframes with interleaving.
    // Here, using av_interleaved_write_frame allows the muxer to get the
    // fragment end durations right. We always set the packet duration to
    // the expected, but we simulate dropped frames at one point.
    do_interleave = 1;
    init_out("vfr-noduration-interleave");
    av_dict_set(&opts, "movflags", "frag_keyframe+delay_moov", 0);
    av_dict_set(&opts, "frag_duration", "650000", 0);
    init_fps(1, 1, 30);
    mux_frames(gop_size/2, 0);
    // Pretend that the packet duration is the normal, even if
    // we actually skip a bunch of frames. (I.e., simulate that
    // we don't know of the framedrop in advance.)
    fake_pkt_duration = duration;
    duration *= 10;
    mux_frames(1, 0);
    fake_pkt_duration = 0;
    duration /= 10;
    mux_frames(gop_size/2 - 1, 0);
    mux_gops(1);
    finish();
    close_out();
    clear_duration = 0;
    do_interleave = 0;

    // Write a fragmented file with b-frames and audio preroll,
    // with negative cts values, removing the edit list for the
    // video track.
    init_out("delay-moov-elst-neg-cts");
    av_dict_set(&opts, "movflags", "frag_keyframe+delay_moov+negative_cts_offsets", 0);
    init(1, 1);
    mux_gops(2);
    finish();
    close_out();

    // Write a fragmented file with b-frames without audio preroll,
    // with negative cts values, avoiding any edit lists, allowing
    // to use empty_moov instead of delay_moov.
    init_out("empty-moov-neg-cts");
    av_dict_set(&opts, "movflags", "frag_keyframe+empty_moov+negative_cts_offsets", 0);
    init(1, 0);
    mux_gops(2);
    finish();
    close_out();

    av_free(md5);

    return check_faults > 0 ? 1 : 0;
}