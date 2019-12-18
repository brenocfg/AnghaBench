#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct SwsContext {int dummy; } ;
struct TYPE_32__ {int count; scalar_t__ found; } ;
typedef  TYPE_3__ ccv_tld_t ;
typedef  int /*<<< orphan*/  ccv_tld_info_t ;
struct TYPE_33__ {int x; int y; int width; int height; } ;
typedef  TYPE_4__ ccv_rect_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
struct TYPE_31__ {double confidence; } ;
struct TYPE_30__ {int x; int y; int width; int height; } ;
struct TYPE_34__ {TYPE_2__ classification; TYPE_1__ rect; } ;
typedef  TYPE_5__ ccv_comp_t ;
struct TYPE_37__ {int nb_streams; TYPE_6__** streams; } ;
struct TYPE_36__ {int /*<<< orphan*/ ** data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_35__ {TYPE_10__* codec; } ;
struct TYPE_29__ {int thread_count; scalar_t__ codec_type; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_6__ AVStream ;
typedef  int /*<<< orphan*/  AVPicture ;
typedef  TYPE_7__ AVPacket ;
typedef  TYPE_7__ AVFrame ;
typedef  TYPE_9__ AVFormatContext ;
typedef  TYPE_10__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_PIX_FMT_RGB24 ; 
 int CCV_IO_GRAY ; 
 int CCV_IO_RGB_RAW ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  PIX_FMT_RGB24 ; 
 int /*<<< orphan*/  SWS_BICUBIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 TYPE_7__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_init_packet (TYPE_7__*) ; 
 int av_read_frame (TYPE_9__*,TYPE_7__*) ; 
 int /*<<< orphan*/  av_register_all () ; 
 TYPE_7__* avcodec_alloc_frame () ; 
 int /*<<< orphan*/  avcodec_decode_video2 (TYPE_10__*,TYPE_7__*,int*,TYPE_7__*) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 scalar_t__ avcodec_open2 (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avformat_find_stream_info (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 int /*<<< orphan*/  avformat_open_input (TYPE_9__**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpicture_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpicture_get_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccfree (int /*<<< orphan*/ *) ; 
 scalar_t__ ccmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_disable_cache () ; 
 int /*<<< orphan*/  ccv_enable_default_cache () ; 
 int /*<<< orphan*/  ccv_matrix_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_read (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ ccv_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_tld_default_params ; 
 int /*<<< orphan*/  ccv_tld_free (TYPE_3__*) ; 
 TYPE_3__* ccv_tld_new (int /*<<< orphan*/ *,TYPE_4__,int /*<<< orphan*/ ) ; 
 TYPE_5__ ccv_tld_track_object (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 struct SwsContext* sws_getCachedContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_scale (struct SwsContext*,int /*<<< orphan*/  const* const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int main(int argc, char** argv)
{
#ifdef HAVE_AVCODEC
#ifdef HAVE_AVFORMAT
#ifdef HAVE_SWSCALE
	assert(argc == 6);
	ccv_rect_t box = ccv_rect(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
	// box.width = box.width - box.x + 1;
	// box.height = box.height - box.y + 1;
	// printf("%d,%d,%d,%d,%f\n", box.x, box.y, box.width + box.x - 1, box.height + box.y - 1, 1.0f);
	printf("%05d: %d %d %d %d %f\n", 0, box.x, box.y, box.width, box.height, 1.0f);
	// init av-related structs
	AVFormatContext* ic = 0;
	int video_stream = -1;
	AVStream* video_st = 0;
	AVFrame* picture = 0;
	AVFrame rgb_picture;
	memset(&rgb_picture, 0, sizeof(AVPicture));
	AVPacket packet;
	memset(&packet, 0, sizeof(AVPacket));
	av_init_packet(&packet);
	av_register_all();
	avformat_network_init();
	// load video and codec
	avformat_open_input(&ic, argv[1], 0, 0);
	avformat_find_stream_info(ic, 0);
	int i;
	for (i = 0; i < ic->nb_streams; i++)
	{
		AVCodecContext* enc = ic->streams[i]->codec;
		enc->thread_count = 2;
		if (AVMEDIA_TYPE_VIDEO == enc->codec_type && video_stream < 0)
		{
			AVCodec* codec = avcodec_find_decoder(enc->codec_id);
			if (!codec || avcodec_open2(enc, codec, 0) < 0)
				continue;
			video_stream = i;
			video_st = ic->streams[i];
#if LIBAVCODEC_VERSION_INT >= AV_VERSION_INT(55, 45, 101)
			picture = av_frame_alloc();
#else
			picture = avcodec_alloc_frame();
#endif
#if LIBAVUTIL_VERSION_MAJOR > 51
			rgb_picture.data[0] = (uint8_t*)ccmalloc(avpicture_get_size(AV_PIX_FMT_RGB24, enc->width, enc->height));
			avpicture_fill((AVPicture*)&rgb_picture, rgb_picture.data[0], AV_PIX_FMT_RGB24, enc->width, enc->height);
#else
			rgb_picture.data[0] = (uint8_t*)ccmalloc(avpicture_get_size(PIX_FMT_RGB24, enc->width, enc->height));
			avpicture_fill((AVPicture*)&rgb_picture, rgb_picture.data[0], PIX_FMT_RGB24, enc->width, enc->height);
#endif
			break;
		}
	}
	int got_picture = 0;
	while (!got_picture)
	{
		int result = av_read_frame(ic, &packet);
		if (result == AVERROR(EAGAIN))
			continue;
		avcodec_decode_video2(video_st->codec, picture, &got_picture, &packet);
	}
	ccv_enable_default_cache();
#if LIBAVUTIL_VERSION_MAJOR > 51
	struct SwsContext* picture_ctx = sws_getCachedContext(0, video_st->codec->width, video_st->codec->height, video_st->codec->pix_fmt, video_st->codec->width, video_st->codec->height, AV_PIX_FMT_RGB24, SWS_BICUBIC, 0, 0, 0);
#else
	struct SwsContext* picture_ctx = sws_getCachedContext(0, video_st->codec->width, video_st->codec->height, video_st->codec->pix_fmt, video_st->codec->width, video_st->codec->height, PIX_FMT_RGB24, SWS_BICUBIC, 0, 0, 0);
#endif
	sws_scale(picture_ctx, (const uint8_t* const*)picture->data, picture->linesize, 0, video_st->codec->height, rgb_picture.data, rgb_picture.linesize);
	ccv_dense_matrix_t* x = 0;
	ccv_read(rgb_picture.data[0], &x, CCV_IO_RGB_RAW | CCV_IO_GRAY, video_st->codec->height, video_st->codec->width, rgb_picture.linesize[0]);
	ccv_tld_t* tld = ccv_tld_new(x, box, ccv_tld_default_params);
	ccv_dense_matrix_t* y = 0;
	for (;;)
	{
		got_picture = 0;
		int result = av_read_frame(ic, &packet);
		if (result == AVERROR(EAGAIN))
			continue;
		avcodec_decode_video2(video_st->codec, picture, &got_picture, &packet);
		if (!got_picture)
			break;
		sws_scale(picture_ctx, (const uint8_t* const*)picture->data, picture->linesize, 0, video_st->codec->height, rgb_picture.data, rgb_picture.linesize);
		ccv_read(rgb_picture.data[0], &y, CCV_IO_RGB_RAW | CCV_IO_GRAY, video_st->codec->height, video_st->codec->width, rgb_picture.linesize[0]);
		ccv_tld_info_t info;
		ccv_comp_t newbox = ccv_tld_track_object(tld, x, y, &info);
		/*
		// printf("%04d: performed learn: %d, performed track: %d, successfully track: %d; %d passed fern detector, %d passed nnc detector, %d merged, %d confident matches, %d close matches\n", tld->count, info.perform_learn, info.perform_track, info.track_success, info.ferns_detects, info.nnc_detects, info.clustered_detects, info.confident_matches, info.close_matches);
		ccv_dense_matrix_t* image = 0;
		ccv_read(rgb_picture.data[0], &image, CCV_IO_RGB_RAW | CCV_IO_RGB_COLOR, video_st->codec->height, video_st->codec->width, rgb_picture.linesize[0]);
		// draw out
		// for (i = 0; i < tld->top->rnum; i++)
		if (tld->found)
		{
			ccv_comp_t* comp = &newbox; // (ccv_comp_t*)ccv_array_get(tld->top, i);
			if (comp->rect.x >= 0 && comp->rect.x + comp->rect.width < image->cols &&
				comp->rect.y >= 0 && comp->rect.y + comp->rect.height < image->rows)
			{
				int x, y;
				for (x = comp->rect.x; x < comp->rect.x + comp->rect.width; x++)
				{
					image->data.u8[image->step * comp->rect.y + x * 3] =
					image->data.u8[image->step * (comp->rect.y + comp->rect.height - 1) + x * 3] = 255;
					image->data.u8[image->step * comp->rect.y + x * 3 + 1] =
					image->data.u8[image->step * (comp->rect.y + comp->rect.height - 1) + x * 3 + 1] =
					image->data.u8[image->step * comp->rect.y + x * 3 + 2] =
					image->data.u8[image->step * (comp->rect.y + comp->rect.height - 1) + x * 3 + 2] = 0;
				}
				for (y = comp->rect.y; y < comp->rect.y + comp->rect.height; y++)
				{
					image->data.u8[image->step * y + comp->rect.x * 3] =
					image->data.u8[image->step * y + (comp->rect.x + comp->rect.width - 1) * 3] = 255;
					image->data.u8[image->step * y + comp->rect.x * 3 + 1] =
					image->data.u8[image->step * y + (comp->rect.x + comp->rect.width - 1) * 3 + 1] =
					image->data.u8[image->step * y + comp->rect.x * 3 + 2] =
					image->data.u8[image->step * y + (comp->rect.x + comp->rect.width - 1) * 3 + 2] = 0;
				}
			}
		}
		char filename[1024];
		sprintf(filename, "tld-out/output-%04d.png", tld->count);
		ccv_write(image, filename, 0, CCV_IO_PNG_FILE, 0);
		ccv_matrix_free(image);
		if (tld->found)
			printf("%d,%d,%d,%d,%f\n", newbox.rect.x, newbox.rect.y, newbox.rect.width + newbox.rect.x - 1, newbox.rect.height + newbox.rect.y - 1, newbox.classification.confidence);
		else
			printf("NaN,NaN,NaN,NaN,NaN\n");
		*/
		if (tld->found)
			printf("%05d: %d %d %d %d %f\n", tld->count, newbox.rect.x, newbox.rect.y, newbox.rect.width, newbox.rect.height, newbox.classification.confidence);
		else
			printf("%05d: --------------\n", tld->count);
		x = y;
		y = 0;
	}
	ccv_matrix_free(x);
	ccv_tld_free(tld);
	ccfree(rgb_picture.data[0]);
	ccv_disable_cache();
#endif
#endif
#endif
	return 0;
}