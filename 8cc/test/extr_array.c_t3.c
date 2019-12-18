__attribute__((used)) static void t3() {
    int a[4][5];
    int *p = a;
    *(*(a + 1) + 2) = 62;
    expect(62, *(p + 7));
}