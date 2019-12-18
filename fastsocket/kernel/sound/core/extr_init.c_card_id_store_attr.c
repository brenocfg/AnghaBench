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
struct snd_card {int /*<<< orphan*/  id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EEXIST ; 
 size_t EINVAL ; 
 struct snd_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_mutex ; 
 struct snd_card** snd_cards ; 
 size_t snd_ecards_limit ; 
 int /*<<< orphan*/  snd_info_card_id_change (struct snd_card*) ; 
 int /*<<< orphan*/  snd_info_check_reserved_words (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
card_id_store_attr(struct device *dev, struct device_attribute *attr,
		   const char *buf, size_t count)
{
	struct snd_card *card = dev_get_drvdata(dev);
	char buf1[sizeof(card->id)];
	size_t copy = count > sizeof(card->id) - 1 ?
					sizeof(card->id) - 1 : count;
	size_t idx;
	int c;

	for (idx = 0; idx < copy; idx++) {
		c = buf[idx];
		if (!isalnum(c) && c != '_' && c != '-')
			return -EINVAL;
	}
	memcpy(buf1, buf, copy);
	buf1[copy] = '\0';
	mutex_lock(&snd_card_mutex);
	if (!snd_info_check_reserved_words(buf1)) {
	     __exist:
		mutex_unlock(&snd_card_mutex);
		return -EEXIST;
	}
	for (idx = 0; idx < snd_ecards_limit; idx++) {
		if (snd_cards[idx] && !strcmp(snd_cards[idx]->id, buf1)) {
			if (card == snd_cards[idx])
				goto __ok;
			else
				goto __exist;
		}
	}
	strcpy(card->id, buf1);
	snd_info_card_id_change(card);
__ok:
	mutex_unlock(&snd_card_mutex);

	return count;
}