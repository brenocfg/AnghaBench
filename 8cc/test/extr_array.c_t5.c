__attribute__((used)) static void t5() {
    int a[2][3];
    a[0][1] = 1;
    a[1][1] = 2;
    int *p = a;
    expect(1, p[1]);
    expect(2, p[4]);
}