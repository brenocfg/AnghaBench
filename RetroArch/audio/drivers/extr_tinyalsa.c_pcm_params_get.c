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
struct snd_pcm_hw_params {int dummy; } ;
struct pcm_params {int dummy; } ;
typedef  int /*<<< orphan*/  fn ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDWR ; 
 unsigned int PCM_IN ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_HW_REFINE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct snd_pcm_hw_params*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct snd_pcm_hw_params*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  param_init (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int,char) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct pcm_params *pcm_params_get(unsigned int card, unsigned int device,
      unsigned int flags)
{
   struct snd_pcm_hw_params *params;
   char fn[256];
   int fd;

   snprintf(fn, sizeof(fn), "/dev/snd/pcmC%uD%u%c", card, device,
         flags & PCM_IN ? 'c' : 'p');

   fd = open(fn, O_RDWR|O_NONBLOCK);
   if (fd < 0)
   {
      fprintf(stderr, "cannot open device '%s'\n", fn);
      goto err_open;
   }

   params = (struct snd_pcm_hw_params*)
      calloc(1, sizeof(struct snd_pcm_hw_params));

   if (!params)
      goto err_calloc;

   param_init(params);
   if (ioctl(fd, SNDRV_PCM_IOCTL_HW_REFINE, params))
   {
      fprintf(stderr, "SNDRV_PCM_IOCTL_HW_REFINE error (%d)\n", errno);
      goto err_hw_refine;
   }

   close(fd);

   return (struct pcm_params *)params;

err_hw_refine:
   free(params);
err_calloc:
   close(fd);
err_open:
   return NULL;
}