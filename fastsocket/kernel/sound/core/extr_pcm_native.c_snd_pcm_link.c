#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_3__* group; int /*<<< orphan*/  link_list; TYPE_2__* runtime; } ;
struct snd_pcm_group {int dummy; } ;
struct snd_pcm_file {struct snd_pcm_substream* substream; } ;
struct file {struct snd_pcm_file* private_data; } ;
struct TYPE_6__ {int count; int /*<<< orphan*/  substreams; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {TYPE_1__* status; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int EALREADY ; 
 int EBADFD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 TYPE_3__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct file* snd_pcm_file_fd (int) ; 
 int /*<<< orphan*/  snd_pcm_link_rwlock ; 
 int /*<<< orphan*/  snd_pcm_link_rwsem ; 
 scalar_t__ snd_pcm_stream_linked (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_link(struct snd_pcm_substream *substream, int fd)
{
	int res = 0;
	struct file *file;
	struct snd_pcm_file *pcm_file;
	struct snd_pcm_substream *substream1;

	file = snd_pcm_file_fd(fd);
	if (!file)
		return -EBADFD;
	pcm_file = file->private_data;
	substream1 = pcm_file->substream;
	down_write(&snd_pcm_link_rwsem);
	write_lock_irq(&snd_pcm_link_rwlock);
	if (substream->runtime->status->state == SNDRV_PCM_STATE_OPEN ||
	    substream->runtime->status->state != substream1->runtime->status->state) {
		res = -EBADFD;
		goto _end;
	}
	if (snd_pcm_stream_linked(substream1)) {
		res = -EALREADY;
		goto _end;
	}
	if (!snd_pcm_stream_linked(substream)) {
		substream->group = kmalloc(sizeof(struct snd_pcm_group), GFP_ATOMIC);
		if (substream->group == NULL) {
			res = -ENOMEM;
			goto _end;
		}
		spin_lock_init(&substream->group->lock);
		INIT_LIST_HEAD(&substream->group->substreams);
		list_add_tail(&substream->link_list, &substream->group->substreams);
		substream->group->count = 1;
	}
	list_add_tail(&substream1->link_list, &substream->group->substreams);
	substream->group->count++;
	substream1->group = substream->group;
 _end:
	write_unlock_irq(&snd_pcm_link_rwlock);
	up_write(&snd_pcm_link_rwsem);
	fput(file);
	return res;
}