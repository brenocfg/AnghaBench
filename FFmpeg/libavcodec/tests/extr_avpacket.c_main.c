#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int INT_MAX ; 
 scalar_t__ av_grow_packet (TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_new_packet (TYPE_1__*,int) ; 
 TYPE_1__* av_packet_clone (TYPE_1__*) ; 
 int /*<<< orphan*/  av_packet_free (TYPE_1__**) ; 
 scalar_t__ av_packet_from_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 scalar_t__ initializations (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(void)
{
    AVPacket avpkt;
    AVPacket *avpkt_clone = NULL;
    int ret = 0;

    if(initializations(&avpkt) < 0){
        printf("failed to initialize variables\n");
        return 1;
    }
    /* test av_packet_clone*/
    avpkt_clone = av_packet_clone(&avpkt);

    if(!avpkt_clone) {
        av_log(NULL, AV_LOG_ERROR,"av_packet_clone failed to clone AVPacket\n");
        return 1;
    }
    /*test av_grow_packet*/
    if(av_grow_packet(avpkt_clone, 20) < 0){
        av_log(NULL, AV_LOG_ERROR, "av_grow_packet failed\n");
        return 1;
    }
    if(av_grow_packet(avpkt_clone, INT_MAX) == 0){
        printf( "av_grow_packet failed to return error "
                "when \"grow_by\" parameter is too large.\n" );
        ret = 1;
    }
    /* test size error check in av_new_packet*/
    if(av_new_packet(avpkt_clone, INT_MAX) == 0){
        printf( "av_new_packet failed to return error "
                "when \"size\" parameter is too large.\n" );
        ret = 1;
    }
    /*test size error check in av_packet_from_data*/
    if(av_packet_from_data(avpkt_clone, avpkt_clone->data, INT_MAX) == 0){
        printf("av_packet_from_data failed to return error "
                "when \"size\" parameter is too large.\n" );
        ret = 1;
    }
    /*clean up*/
    av_packet_free(&avpkt_clone);
    av_packet_unref(&avpkt);


    return ret;
}