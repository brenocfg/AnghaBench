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
struct snd_seq_client {int dummy; } ;

/* Variables and functions */
 int SNDRV_SEQ_MAX_CLIENTS ; 
 struct snd_seq_client** clienttab ; 
 int /*<<< orphan*/  snd_printd (char*,int) ; 

__attribute__((used)) static struct snd_seq_client *clientptr(int clientid)
{
	if (clientid < 0 || clientid >= SNDRV_SEQ_MAX_CLIENTS) {
		snd_printd("Seq: oops. Trying to get pointer to client %d\n",
			   clientid);
		return NULL;
	}
	return clienttab[clientid];
}