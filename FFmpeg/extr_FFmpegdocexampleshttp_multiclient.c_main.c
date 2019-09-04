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
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/  av_log_set_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 int avio_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ *) ; 
 int avio_open2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  process_client (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    AVDictionary *options = NULL;
    AVIOContext *client = NULL, *server = NULL;
    const char *in_uri, *out_uri;
    int ret, pid;
    av_log_set_level(AV_LOG_TRACE);
    if (argc < 3) {
        printf("usage: %s input http://hostname[:port]\n"
               "API example program to serve http to multiple clients.\n"
               "\n", argv[0]);
        return 1;
    }

    in_uri = argv[1];
    out_uri = argv[2];

    avformat_network_init();

    if ((ret = av_dict_set(&options, "listen", "2", 0)) < 0) {
        fprintf(stderr, "Failed to set listen mode for server: %s\n", av_err2str(ret));
        return ret;
    }
    if ((ret = avio_open2(&server, out_uri, AVIO_FLAG_WRITE, NULL, &options)) < 0) {
        fprintf(stderr, "Failed to open server: %s\n", av_err2str(ret));
        return ret;
    }
    fprintf(stderr, "Entering main loop.\n");
    for(;;) {
        if ((ret = avio_accept(server, &client)) < 0)
            goto end;
        fprintf(stderr, "Accepted client, forking process.\n");
        // XXX: Since we don't reap our children and don't ignore signals
        //      this produces zombie processes.
        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            ret = AVERROR(errno);
            goto end;
        }
        if (pid == 0) {
            fprintf(stderr, "In child.\n");
            process_client(client, in_uri);
            avio_close(server);
            exit(0);
        }
        if (pid > 0)
            avio_close(client);
    }
end:
    avio_close(server);
    if (ret < 0 && ret != AVERROR_EOF) {
        fprintf(stderr, "Some errors occurred: %s\n", av_err2str(ret));
        return 1;
    }
    return 0;
}