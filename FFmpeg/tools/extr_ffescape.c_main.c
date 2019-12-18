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
typedef  enum AVEscapeMode { ____Placeholder_AVEscapeMode } AVEscapeMode ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int AV_ESCAPE_FLAG_STRICT ; 
 int AV_ESCAPE_FLAG_WHITESPACE ; 
 int AV_ESCAPE_MODE_AUTO ; 
 int AV_ESCAPE_MODE_BACKSLASH ; 
 int AV_ESCAPE_MODE_QUOTE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int EOF ; 
 long INT_MAX ; 
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  av_bprint_finalize (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprint_is_complete (int /*<<< orphan*/ *) ; 
 scalar_t__ av_escape (char**,char*,char*,int,int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int getopt (int,char**,char*) ; 
 char const* optarg ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 long strtol (char const*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
    AVBPrint src;
    char *src_buf, *dst_buf;
    const char *outfilename = NULL, *infilename = NULL;
    FILE *outfile = NULL, *infile = NULL;
    const char *prompt = "=> ";
    enum AVEscapeMode escape_mode = AV_ESCAPE_MODE_AUTO;
    int escape_flags = 0;
    int level = 1;
    int echo = 0;
    char *special_chars = NULL;
    int c;

    while ((c = getopt(argc, argv, "ef:hi:l:o:m:p:s:")) != -1) {
        switch (c) {
        case 'e':
            echo = 1;
            break;
        case 'h':
            usage();
            return 0;
        case 'i':
            infilename = optarg;
            break;
        case 'f':
            if      (!strcmp(optarg, "whitespace")) escape_flags |= AV_ESCAPE_FLAG_WHITESPACE;
            else if (!strcmp(optarg, "strict"))     escape_flags |= AV_ESCAPE_FLAG_STRICT;
            else {
                av_log(NULL, AV_LOG_ERROR,
                       "Invalid value '%s' for option -f, "
                       "valid arguments are 'whitespace', and 'strict'\n", optarg);
                return 1;
            }
            break;
        case 'l':
        {
            char *tail;
            long int li = strtol(optarg, &tail, 10);
            if (*tail || li > INT_MAX || li < 0) {
                av_log(NULL, AV_LOG_ERROR,
                        "Invalid value '%s' for option -l, argument must be a non negative integer\n",
                        optarg);
                return 1;
            }
            level = li;
            break;
        }
        case 'm':
            if      (!strcmp(optarg, "auto"))      escape_mode = AV_ESCAPE_MODE_AUTO;
            else if (!strcmp(optarg, "backslash")) escape_mode = AV_ESCAPE_MODE_BACKSLASH;
            else if (!strcmp(optarg, "quote"))     escape_mode = AV_ESCAPE_MODE_QUOTE;
            else {
                av_log(NULL, AV_LOG_ERROR,
                       "Invalid value '%s' for option -m, "
                       "valid arguments are 'backslash', and 'quote'\n", optarg);
                return 1;
            }
            break;
        case 'o':
            outfilename = optarg;
            break;
        case 'p':
            prompt = optarg;
            break;
        case 's':
            special_chars = optarg;
            break;
        case '?':
            return 1;
        }
    }

    if (!infilename || !strcmp(infilename, "-")) {
        infilename = "stdin";
        infile = stdin;
    } else {
        infile = fopen(infilename, "r");
    }
    if (!infile) {
        av_log(NULL, AV_LOG_ERROR, "Impossible to open input file '%s': %s\n", infilename, strerror(errno));
        return 1;
    }

    if (!outfilename || !strcmp(outfilename, "-")) {
        outfilename = "stdout";
        outfile = stdout;
    } else {
        outfile = fopen(outfilename, "w");
    }
    if (!outfile) {
        av_log(NULL, AV_LOG_ERROR, "Impossible to open output file '%s': %s\n", outfilename, strerror(errno));
        return 1;
    }

    /* grab the input and store it in src */
    av_bprint_init(&src, 1, AV_BPRINT_SIZE_UNLIMITED);
    while ((c = fgetc(infile)) != EOF)
        av_bprint_chars(&src, c, 1);
    av_bprint_chars(&src, 0, 1);

    if (!av_bprint_is_complete(&src)) {
        av_log(NULL, AV_LOG_ERROR, "Could not allocate a buffer for the source string\n");
        av_bprint_finalize(&src, NULL);
        return 1;
    }
    av_bprint_finalize(&src, &src_buf);

    if (echo)
        fprintf(outfile, "%s", src_buf);

    /* escape */
    dst_buf = src_buf;
    while (level--) {
        if (av_escape(&dst_buf, src_buf, special_chars, escape_mode, escape_flags) < 0) {
            av_log(NULL, AV_LOG_ERROR, "Could not escape string\n");
            return 1;
        }
        av_free(src_buf);
        src_buf = dst_buf;
    }

    fprintf(outfile, "%s%s", prompt, dst_buf);
    av_free(dst_buf);
    return 0;
}