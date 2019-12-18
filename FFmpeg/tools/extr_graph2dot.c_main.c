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
struct line {int /*<<< orphan*/  data; struct line* next; } ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  AVFilterGraph ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log_set_level (int /*<<< orphan*/ ) ; 
 void* av_malloc (int) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 scalar_t__ avfilter_graph_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ avfilter_graph_parse (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 char* optarg ; 
 int /*<<< orphan*/  print_digraph (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
    const char *outfilename = NULL;
    const char *infilename  = NULL;
    FILE *outfile           = NULL;
    FILE *infile            = NULL;
    char *graph_string      = NULL;
    AVFilterGraph *graph = av_mallocz(sizeof(AVFilterGraph));
    char c;

    av_log_set_level(AV_LOG_DEBUG);

    while ((c = getopt(argc, argv, "hi:o:")) != -1) {
        switch (c) {
        case 'h':
            usage();
            return 0;
        case 'i':
            infilename = optarg;
            break;
        case 'o':
            outfilename = optarg;
            break;
        case '?':
            return 1;
        }
    }

    if (!infilename || !strcmp(infilename, "-"))
        infilename = "/dev/stdin";
    infile = fopen(infilename, "r");
    if (!infile) {
        fprintf(stderr, "Failed to open input file '%s': %s\n",
                infilename, strerror(errno));
        return 1;
    }

    if (!outfilename || !strcmp(outfilename, "-"))
        outfilename = "/dev/stdout";
    outfile = fopen(outfilename, "w");
    if (!outfile) {
        fprintf(stderr, "Failed to open output file '%s': %s\n",
                outfilename, strerror(errno));
        return 1;
    }

    /* read from infile and put it in a buffer */
    {
        int64_t count = 0;
        struct line *line, *last_line, *first_line;
        char *p;
        last_line = first_line = av_malloc(sizeof(struct line));
        if (!last_line) {
            fprintf(stderr, "Memory allocation failure\n");
            return 1;
        }

        while (fgets(last_line->data, sizeof(last_line->data), infile)) {
            struct line *new_line = av_malloc(sizeof(struct line));
            if (!new_line) {
                fprintf(stderr, "Memory allocation failure\n");
                return 1;
            }
            count += strlen(last_line->data);
            last_line->next = new_line;
            last_line       = new_line;
        }
        last_line->next = NULL;

        graph_string = av_malloc(count + 1);
        if (!graph_string) {
            fprintf(stderr, "Memory allocation failure\n");
            return 1;
        }
        p = graph_string;
        for (line = first_line; line->next; line = line->next) {
            size_t l = strlen(line->data);
            memcpy(p, line->data, l);
            p += l;
        }
        *p = '\0';
    }

    if (avfilter_graph_parse(graph, graph_string, NULL, NULL, NULL) < 0) {
        fprintf(stderr, "Failed to parse the graph description\n");
        return 1;
    }

    if (avfilter_graph_config(graph, NULL) < 0)
        return 1;

    print_digraph(outfile, graph);
    fflush(outfile);

    return 0;
}