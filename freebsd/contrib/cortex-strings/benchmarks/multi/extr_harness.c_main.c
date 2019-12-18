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
typedef  int /*<<< orphan*/  (* stub_t ) (char*,char*,int) ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct test {char* name; int /*<<< orphan*/  (* stub ) (char*,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_PROCESS_CPUTIME_ID ; 
 int MAX_ALIGNMENT ; 
 int MIN_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  empty (char*) ; 
 struct test* find_test (char const*) ; 
 int getopt (int,char**,char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  parse_alignment_arg (int /*<<< orphan*/ ,char*,int*,int*) ; 
 int parse_int_arg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int,int,int,int,char const*,double,double,int,char*,int,double) ; 
 scalar_t__ random () ; 
 char* realign (char*,int) ; 
 int /*<<< orphan*/  srandom (int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  stub1 (char*,char*,int) ; 
 int /*<<< orphan*/  stub2 (char*,char*,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv)
{
  /* Size of src and dest buffers */
  size_t buffer_size = MIN_BUFFER_SIZE;

  /* Number of bytes per call */
  int count = 31;
  /* Number of times to run */
  int loops = 10000000;
  /* True to flush the cache each time */
  int flush = 0;
  /* Name of the test */
  const char *name = NULL;
  /* Alignment of buffers */
  int src_alignment = 8;
  int dst_alignment = 8;
  /* Name of the run */
  const char *run_id = "0";

  int opt;

  while ((opt = getopt(argc, argv, "c:l:ft:r:hva:")) > 0)
    {
      switch (opt)
	{
	case 'c':
          count = parse_int_arg(optarg, argv[0]);
          break;
	case 'l':
          loops = parse_int_arg(optarg, argv[0]);
          break;
	case 'a':
          parse_alignment_arg(optarg, argv[0], &src_alignment, &dst_alignment);
          break;
	case 'f':
          flush = 1;
          break;
	case 't':
          name = strdup(optarg);
          break;
	case 'r':
          run_id = strdup(optarg);
          break;
	case 'h':
          usage(argv[0]);
          break;
	default:
          usage(argv[0]);
          break;
	}
    }

  /* Find the test by name */
  const struct test *ptest = find_test(name);

  if (ptest == NULL)
    {
      usage(argv[0]);
    }

  if (count + MAX_ALIGNMENT * 2 > MIN_BUFFER_SIZE)
    {
      buffer_size = count + MAX_ALIGNMENT * 2;
    }

  /* Buffers to read and write from */
  char *src = malloc(buffer_size);
  char *dest = malloc(buffer_size);

  assert(src != NULL && dest != NULL);

  src = realign(src, src_alignment);
  dest = realign(dest, dst_alignment);

  /* Fill the buffer with non-zero, reproducable random data */
  srandom(1539);

  for (int i = 0; i < buffer_size; i++)
    {
      src[i] = (char)random() | 1;
      dest[i] = src[i];
    }

  /* Make sure the buffers are null terminated for any string tests */
  src[count] = 0;
  dest[count] = 0;

  struct timespec start, end;
  int err = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  assert(err == 0);

  /* Preload */
  stub_t stub = ptest->stub;

  /* Run two variants to reduce the cost of testing for the flush */
  if (flush == 0)
    {
      for (int i = 0; i < loops; i++)
	{
	  (*stub)(dest, src, count);
	}
    }
  else
    {
      for (int i = 0; i < loops; i++)
	{
	  (*stub)(dest, src, count);
	  empty(dest);
	}
    }

  err = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
  assert(err == 0);

  /* Drop any leading path and pull the variant name out of the executable */
  char *variant = strrchr(argv[0], '/');

  if (variant == NULL)
    {
      variant = argv[0];
    }

  variant = strstr(variant, "try-");
  assert(variant != NULL);

  double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
  /* Estimate the bounce time.  Measured on a Panda. */
  double bounced = 0.448730 * loops / 50000000;

  /* Dump both machine and human readable versions */
  printf("%s:%s:%u:%u:%d:%d:%s:%.6f: took %.6f s for %u calls to %s of %u bytes.  ~%.3f MB/s corrected.\n", 
         variant + 4, ptest->name,
	 count, loops, src_alignment, dst_alignment, run_id,
	 elapsed,
         elapsed, loops, ptest->name, count,
         (double)loops*count/(elapsed - bounced)/(1024*1024));

  return 0;
}